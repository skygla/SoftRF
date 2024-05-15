/*
 * TimeHelper.cpp
 * Copyright (C) 2016-2021 Linar Yusupov
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "SoC.h"
#include "../driver/GNSS.h"
#include "../driver/RF.h"
#include "../driver/EEPROM.h"

time_t  OurTime = 0;           /* UTC time in seconds since start of 1970 */
uint32_t base_time_ms = 0;     /* this device millis() at last verified PPS */
uint32_t ref_time_ms = 0;      /* assumed local millis() at last PPS */

#define ADJ_FOR_FLARM_RECEPTION 25     // was 40 - seemed to receive FLARM packets better that way

#if defined(EXCLUDE_WIFI)
void Time_setup()     {}
#else

#include <TimeLib.h>

unsigned int localPort = 2390;      // local port to listen for UDP packets

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
//IPAddress timeServer(129, 6, 15, 28); // time.nist.gov NTP server
IPAddress timeServerIP; // time.nist.gov NTP server address
//const char* ntpServerName = "time.nist.gov";
const String ntpServerName_suffix = ".pool.ntp.org";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message

byte NTPPacketBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP NTP_udp;

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress& address)
{
  Serial.println(F("sending NTP packet..."));
  // set all bytes in the buffer to 0
  memset(NTPPacketBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  NTPPacketBuffer[0] = 0b11100011;   // LI, Version, Mode
  NTPPacketBuffer[1] = 0;     // Stratum, or type of clock
  NTPPacketBuffer[2] = 6;     // Polling Interval
  NTPPacketBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  NTPPacketBuffer[12]  = 49;
  NTPPacketBuffer[13]  = 0x4E;
  NTPPacketBuffer[14]  = 49;
  NTPPacketBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  NTP_udp.beginPacket(address, 123); //NTP requests are to port 123
  NTP_udp.write(NTPPacketBuffer, NTP_PACKET_SIZE);
  NTP_udp.endPacket();
}

void Time_setup()
{
  int cb = 0;
  String ntpServerName;

  // Do not attempt to timesync in Soft AP mode
  if (WiFi.getMode() == WIFI_AP) {
    return;
  }

  Serial.println(F("Starting NTP UDP"));
  NTP_udp.begin(localPort);
  Serial.print(F("Local port: "));
  Serial.println(localPort);

  for (int attempt = 1; attempt <= 4; attempt++ ) {

    //get a random server from the pool
    ntpServerName = String(attempt-1) + ntpServerName_suffix;
    WiFi.hostByName(ntpServerName.c_str(), timeServerIP);

    Serial.print('#');
    Serial.print(attempt);
    Serial.print(F(" NTP server's IP address: "));
    Serial.println(timeServerIP);

    sendNTPpacket(timeServerIP); // send an NTP packet to a time server

    // wait to see if a reply is available
    delay(2000);

    cb = NTP_udp.parsePacket();
    if (!cb) {
      Serial.print(F("No response on request #"));
      Serial.println(attempt);
      continue;
    }
    else {
      Serial.print(F("Reply packet received, length="));
      Serial.println(cb);
      // We've received a packet, read the data from it
      NTP_udp.read(NTPPacketBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
      break;
    }
  }

  NTP_udp.stop();

  if (!cb) {
    Serial.println(F("WARNING! Unable to sync time by NTP."));
    return;
  }

  //the timestamp starts at byte 40 of the received packet and is four bytes,
  // or two words, long. First, esxtract the two words:

  unsigned long highWord = word(NTPPacketBuffer[40], NTPPacketBuffer[41]);
  unsigned long lowWord = word(NTPPacketBuffer[42], NTPPacketBuffer[43]);
  // combine the four bytes (two words) into a long integer
  // this is NTP time (seconds since Jan 1 1900):
  unsigned long secsSince1900 = highWord << 16 | lowWord;
  Serial.print(F("Seconds since Jan 1 1900 = "));
  Serial.println(secsSince1900);

  // now convert NTP time into everyday time:
  Serial.print(F("Unix time = "));
  // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
  const unsigned long seventyYears = 2208988800UL;
  // subtract seventy years:
  unsigned long epoch = secsSince1900 - seventyYears;
  // print Unix time:
  Serial.println(epoch);

  setTime((time_t) epoch);

  // print the hour, minute and second:
  Serial.print(F("The UTC time is "));       // UTC is the time at Greenwich Meridian (GMT)
  Serial.print((epoch  % 86400L) / 3600); // print the hour (86400 equals secs per day)
  Serial.print(':');
  if ( ((epoch % 3600) / 60) < 10 ) {
    // In the first 10 minutes of each hour, we'll want a leading '0'
    Serial.print('0');
  }
  Serial.print((epoch  % 3600) / 60); // print the minute (3600 equals secs per minute)
  Serial.print(':');
  if ( (epoch % 60) < 10 ) {
    // In the first 10 seconds of each minute, we'll want a leading '0'
    Serial.print('0');
  }
  Serial.println(epoch % 60); // print the second
}

#endif /* EXCLUDE_WIFI */


/* Experimental code by Moshe Braner, specific to Legacy Protocol */
void Time_loop()
{
    uint32_t now_ms = millis();

#if 0
    // gather some data on how often the main loop() goes around
    static uint32_t last_loop = 0;
    static uint32_t counter = 0;
    static int min_loop = 9999;
    static int max_loop = 0;
    static uint32_t initial_time;
    if (last_loop > 0) {
        int interval = now_ms - last_loop;
        if (interval < min_loop)
            min_loop = interval;
        if (interval > max_loop)
            max_loop = interval;
        ++counter;
        if (counter >= (1<<13)) {
            Serial.printf("loop() ms: min %d, max %d, avg %d/16\r\n",
                            min_loop, max_loop, ((now_ms-initial_time)>>(13-4)));
            counter = 0;
            min_loop = 9999;
            max_loop = 0;
            initial_time = now_ms;
        }
    } else {
        initial_time = now_ms;
    }
    last_loop = now_ms;
#endif

    if (settings->rf_protocol != RF_PROTOCOL_LEGACY
     && settings->rf_protocol != RF_PROTOCOL_LATEST
     && settings->rf_protocol != RF_PROTOCOL_OGNTP)
        return;       /* time still handled in RF.cpp RF_SetChannel() */

    uint32_t gnss_age = gnss.time.age();
    uint32_t last_Commit_Time = now_ms - gnss_age;
    bool newfix = false;
    
    uint32_t pps_btime_ms;
    uint32_t newtime;
    uint32_t time_corr_neg;

    if (isValidFix()) {

        pps_btime_ms = SoC->get_PPS_TimeMarker();
        if (pps_btime_ms > 0) {
          if (now_ms > pps_btime_ms + 1010)
            pps_btime_ms += 1000;
          newtime = pps_btime_ms + ADJ_FOR_FLARM_RECEPTION;   /* seems to receive FLARM better */
        } else {   /* PPS not available */
          time_corr_neg = gnss_chip ? gnss_chip->rmc_ms : 100;
          newtime = last_Commit_Time - time_corr_neg;
        }
    
        if (gnss_age < 2500 && newtime > base_time_ms) {
            static uint32_t lasttime_ms = 0;
            if (last_Commit_Time - lasttime_ms > 150) {     /* new data arrived from GNSS */
                newfix = true;
                lasttime_ms = last_Commit_Time;
            }
        }
    }

    /* between fixes (but not before first fix): free-running clock */
    if (! newfix) {
        if (ref_time_ms > 0 && now_ms >= ref_time_ms + 1000) {
          OurTime += 1;
          ref_time_ms += 1000;
        }
        return;
    }

    if (pps_btime_ms > 0) {
      if (now_ms > pps_btime_ms + 1010) {
        pps_btime_ms += 1000;
        newtime += 1000;
      }
      if (pps_btime_ms <= last_Commit_Time) {
        time_corr_neg = (last_Commit_Time - pps_btime_ms) % 1000;
      } else {
        time_corr_neg = 1000 - ((pps_btime_ms - last_Commit_Time) % 1000);
      }
      ref_time_ms = base_time_ms = newtime;  // = pps_btime_ms + ADJ_FOR_FLARM_RECEPTION
      /* the adjusted time seems to better fit actual FLARM time slots */
    } else {
      //uint32_t last_RMC_Commit = now_ms - gnss.date.age();
      //time_corr_neg = gnss_chip ? gnss_chip->rmc_ms : 100;
      ref_time_ms = base_time_ms = newtime;
    }

    int yr = gnss.date.year();
    if( yr > 99)
        yr = yr - 1970;
    else
        yr += 30;
    tmElements_t tm;
    tm.Year   = yr;
    tm.Month  = gnss.date.month();
    tm.Day    = gnss.date.day();
    tm.Hour   = gnss.time.hour();
    tm.Minute = gnss.time.minute();
    tm.Second = gnss.time.second();

    OurTime = makeTime(tm) + (gnss.time.age() + time_corr_neg) / 1000;
    /* updated ref_time_ms is the other side effect */

    /* system clock also gets updated, by GNSSTimeSync() called from GNSS_loop() */
}
