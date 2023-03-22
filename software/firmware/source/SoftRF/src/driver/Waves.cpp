#if defined(ARDUINO)
#include <Arduino.h>
#endif

#if !defined(EXCLUDE_VOICE)
#if defined(ESP32)

#include "../../SoftRF.h"
#include "Voice.h"

#include "SPIFFS.h"
// #include <FS.h>

// C table generated from file: traffic.wav - sans header

#define DEFAULTSIZE 3470
const uint8_t defaultwav[DEFAULTSIZE] PROGMEM = {
126,131,125,130,131,127,127,133,125,128,131,127,131,
127,130,130,129,129,126,132,120,129,137,121,132,134,122,130,133,123,131,130,
120,140,123,121,141,126,119,140,121,106,133,128,125,133,132,129,124,150,95,
153,125,118,131,146,106,136,147,112,129,142,128,118,150,111,138,132,118,138,
131,113,150,105,149,121,116,151,107,139,125,119,143,115,134,117,145,107,132,
132,125,106,158,109,113,156,107,130,129,124,124,125,131,113,137,124,120,130,
122,138,110,132,139,113,134,118,150,102,132,146,103,136,135,111,146,107,153,
112,122,155,103,137,134,126,126,128,139,118,130,146,108,139,132,132,107,161,
105,139,122,133,130,115,139,134,111,139,139,121,116,157,126,91,181,109,99,
187,84,145,136,114,145,108,156,108,127,150,114,117,149,122,127,119,146,119,
105,143,120,131,120,132,138,126,124,132,133,122,133,126,119,155,110,117,171,
100,143,120,144,128,116,134,154,93,128,155,105,120,160,89,137,147,104,130,
128,139,126,118,130,141,111,119,128,135,93,158,107,111,152,116,118,128,127,
140,99,141,134,118,132,130,137,117,138,134,117,139,120,125,137,119,141,108,
138,137,116,116,138,133,117,124,139,127,128,120,142,119,139,113,134,138,110,
138,120,132,125,124,130,123,131,133,117,135,134,117,142,127,122,137,128,118,
134,119,147,108,131,152,125,124,121,143,126,116,129,139,119,130,139,126,131,
142,122,132,135,137,119,130,139,131,132,124,140,122,130,136,109,127,143,111,
126,137,122,141,119,140,115,148,126,108,137,133,109,128,118,131,117,135,129,
113,135,133,116,131,124,128,123,119,134,108,136,128,112,127,148,112,132,136,
127,122,134,131,117,137,129,122,125,138,121,134,137,109,109,135,122,126,110,
146,123,129,131,121,138,122,139,120,144,139,126,139,145,131,129,133,143,125,
124,127,139,124,120,125,123,123,125,121,129,125,141,131,137,128,123,147,123,
107,145,130,127,131,111,141,128,118,114,123,141,117,116,136,130,129,122,134,
130,125,117,143,115,114,131,122,124,119,117,127,126,124,116,120,136,123,120,
131,130,135,133,129,137,137,137,122,136,128,134,137,128,123,141,141,123,137,
123,126,129,124,129,125,118,139,130,126,139,125,134,131,132,134,126,126,132,
133,133,123,126,142,127,129,120,137,127,127,130,128,126,125,131,129,122,126,
126,141,124,123,134,123,133,121,131,127,128,133,124,126,126,117,131,143,128,
118,132,136,130,117,121,135,133,127,129,129,126,125,135,124,120,131,135,124,
124,137,132,124,131,130,125,129,130,135,126,124,133,135,120,118,126,125,124,
121,118,124,128,123,116,129,125,125,123,125,125,126,135,124,132,136,141,137,
138,142,137,131,122,124,128,126,121,120,126,124,117,117,119,115,114,116,119,
121,120,121,123,128,132,144,146,140,147,156,159,156,149,135,121,119,116,110,
109,120,133,132,125,123,118,110,103,107,117,120,123,128,131,129,127,135,148,
153,153,154,168,180,147,107,94,110,110,98,106,134,149,141,133,130,124,107,
88,90,103,119,130,131,130,134,133,123,120,141,170,169,157,178,189,122,61,
74,120,110,88,121,171,171,137,127,133,118,92,89,86,98,119,144,144,134,
132,135,120,109,124,165,184,176,178,194,141,63,56,106,112,90,118,178,185,
150,132,133,112,87,89,108,101,100,138,162,137,115,125,130,108,100,129,167,
183,179,174,198,170,62,27,82,125,105,117,174,193,162,136,125,96,77,86,
113,118,125,142,149,127,109,115,120,107,117,135,148,147,165,179,172,171,195,
101,5,58,138,136,105,162,196,171,131,118,87,68,88,127,130,128,145,146,
121,101,106,117,117,128,138,143,143,155,168,170,165,191,143,19,36,126,146,
114,155,194,165,132,121,83,58,94,134,136,132,146,141,112,97,104,115,124,
135,140,138,133,134,147,165,165,159,182,160,42,42,115,138,123,163,184,147,
132,126,85,63,107,135,135,130,138,127,111,112,113,115,132,140,131,128,130,
134,153,167,158,152,168,157,77,56,103,126,135,162,166,136,135,125,86,80,
115,128,123,132,129,118,130,121,105,117,136,126,126,132,128,141,161,150,136,
150,161,150,120,86,92,123,136,138,142,143,138,117,100,98,112,111,109,132,
136,129,126,120,111,114,126,127,129,135,134,140,151,136,130,146,143,158,157,
109,102,131,125,110,138,143,132,133,119,106,109,100,116,143,133,122,133,125,
110,118,118,129,145,140,126,132,143,128,127,141,142,140,152,139,117,133,128,
111,127,139,124,136,127,115,109,123,124,123,135,115,118,128,128,116,125,127,
142,127,122,133,132,136,130,129,132,144,138,123,144,136,124,127,133,128,126,
141,113,134,130,114,129,124,131,120,121,126,128,128,124,120,122,126,131,125,
123,137,125,124,126,127,133,131,118,139,128,127,132,136,131,135,125,125,129,
115,139,127,133,134,122,125,123,128,131,117,140,119,114,137,129,123,133,138,
111,139,125,109,137,142,111,140,135,128,126,127,114,152,124,125,125,136,136,
125,126,133,128,130,120,117,140,120,127,121,124,112,139,113,123,128,124,123,
126,119,127,134,112,130,134,121,141,126,120,134,130,119,134,138,120,122,151,
108,133,121,123,120,133,123,117,137,130,135,105,126,122,135,122,131,126,140,
123,135,111,134,128,135,128,140,120,130,135,129,138,138,133,132,129,129,140,
125,150,124,144,122,135,127,127,132,135,127,137,135,123,139,136,120,133,128,
123,138,130,120,138,124,117,134,124,125,131,119,127,132,123,135,127,123,127,
135,123,130,133,123,132,131,114,139,133,121,133,130,130,131,133,123,137,134,
129,130,135,126,134,131,123,139,124,126,136,126,131,129,128,127,126,127,121,
124,133,122,121,130,119,124,123,127,127,127,130,130,127,119,124,122,127,119,
128,118,122,124,117,130,115,125,132,121,127,126,127,128,129,124,128,128,133,
122,129,127,124,126,128,126,128,128,130,126,135,125,129,132,123,129,127,126,
136,124,128,134,123,136,126,129,134,127,129,132,128,130,129,131,130,131,126,
131,129,127,125,127,127,126,129,127,128,126,128,126,125,130,126,129,131,127,
129,127,129,127,130,128,127,132,126,129,130,128,131,129,129,129,128,131,129,
131,131,128,129,130,128,130,129,128,129,127,130,128,130,128,130,128,128,129,
128,128,128,128,127,129,127,128,127,130,127,127,130,127,129,128,129,130,127,
128,128,128,128,129,127,128,129,128,127,128,127,128,127,128,127,127,127,127,
129,126,128,127,127,127,128,126,127,128,127,129,128,127,129,127,128,128,128,
129,127,129,128,128,130,128,130,127,129,129,127,128,127,128,128,128,127,128,
126,128,127,127,127,126,128,127,126,128,125,127,128,126,128,128,127,128,128,
128,129,127,129,127,129,128,129,127,130,129,129,128,129,128,130,129,130,128,
130,130,128,129,130,129,129,130,129,130,129,130,128,130,126,130,130,128,127,
131,126,129,128,127,129,127,127,127,128,127,127,128,126,128,127,126,127,128,
127,127,127,126,127,125,126,129,126,127,127,127,126,127,127,128,128,126,129,
127,128,127,129,128,128,129,128,128,128,129,128,128,128,129,127,130,128,129,
130,128,130,128,128,130,128,127,131,127,130,128,130,128,127,131,127,129,129,
128,129,129,128,127,128,129,128,126,129,127,127,128,126,128,127,126,127,127,
127,127,126,128,126,127,127,126,128,125,128,126,126,127,127,127,126,128,126,
127,128,128,126,129,127,127,126,127,127,126,126,128,126,126,129,126,128,127,
127,127,128,128,127,128,128,127,127,128,127,128,128,127,128,128,129,128,127,
130,127,127,129,128,129,128,129,129,129,129,130,129,129,127,130,129,127,130,
129,129,130,129,129,130,129,130,129,129,129,129,129,129,128,129,128,128,130,
127,128,129,127,128,127,128,127,126,127,127,126,128,127,128,126,129,128,127,
129,127,129,129,128,128,131,128,131,130,128,130,127,130,130,128,130,129,129,
128,131,126,129,128,128,129,128,129,129,129,129,130,128,129,128,128,129,128,
129,128,128,130,128,127,130,128,127,128,129,128,129,126,128,129,127,129,127,
128,130,127,127,130,126,131,128,128,130,129,129,128,129,129,129,126,129,127,
127,126,128,127,127,127,128,127,127,127,127,126,126,128,126,128,128,125,130,
125,128,127,126,128,127,127,126,127,126,126,126,125,128,126,127,127,126,129,
125,129,127,126,128,126,128,126,128,128,127,128,128,129,128,129,129,129,129,
128,130,129,128,130,127,130,129,128,131,128,129,131,128,130,130,129,128,129,
126,129,128,128,129,128,128,128,126,127,126,125,127,127,127,128,129,130,130,
131,133,133,134,135,137,130,136,136,131,133,131,129,129,122,128,126,121,130,
129,126,130,127,128,126,125,128,124,123,126,125,123,126,123,125,126,124,129,
127,128,133,134,138,139,140,145,142,146,143,110,130,122,96,115,118,120,126,
126,148,133,131,143,126,122,119,117,118,111,122,126,121,133,134,132,132,126,
122,128,114,121,128,122,130,132,137,140,139,149,141,143,148,144,139,105,135,
116,92,123,120,120,127,137,149,126,139,141,117,120,119,114,112,114,128,119,
125,138,131,130,132,128,124,105,129,116,108,136,123,133,135,139,144,133,148,
140,137,147,139,135,104,136,111,94,126,116,122,127,139,145,122,142,135,115,
124,118,115,113,118,128,119,131,137,129,132,133,125,115,128,116,119,127,126,
133,132,140,141,140,146,140,143,146,139,144,110,130,121,95,124,116,121,127,
135,143,130,140,137,121,126,120,115,115,119,123,121,130,133,130,134,130,127,
118,124,118,116,128,123,129,134,135,140,138,144,141,139,147,139,143,135,105,
143,104,102,127,113,126,125,142,138,126,150,127,121,129,116,117,114,123,122,
120,135,131,130,134,133,123,119,131,114,118,132,123,130,135,139,134,141,147,
138,140,148,138,146,126,112,141,94,112,126,112,125,131,143,132,135,147,122,
126,128,115,115,118,122,120,124,136,130,131,139,129,126,128,120,115,122,116,
125,125,134,135,135,142,139,139,143,138,143,137,149,120,113,146,89,116,127,
112,124,134,142,130,135,147,119,126,130,113,115,121,120,118,125,135,126,132,
137,127,128,128,121,113,119,118,116,127,124,134,132,138,138,135,139,137,135,
141,136,147,121,112,147,88,116,126,110,125,130,140,128,135,146,119,128,130,
114,117,122,119,118,126,133,125,134,138,129,131,133,124,123,123,124,120,124,
128,126,117,139,129,121,143,131,131,139,136,138,134,150,140,145,130,116,143,
98,113,128,109,126,132,139,135,135,148,125,128,132,114,118,120,118,119,123,
135,129,132,143,132,131,135,127,123,123,124,119,122,128,125,130,133,133,132,
132,133,126,127,123,116,129,118,123,135,126,135,137,133,136,133,135,130,133,
133,134,135,135,128,128,133,109,131,122,113,134,123,127,133,132,134,124,132,
128,119,127,122,118,124,124,126,127,131,131,128,132,129,125,125,125,123,123,
125,126,125,128,129,128,130,128,122,133,121,123,131,123,126,131,130,130,130,
135,131,133,138,133,132,128,126,119,121,119,120,125,126,130,133,133,133,131,
131,127,125,125,123,122,124,126,127,130,131,131,131,132,130,129,129,127,126,
126,126,126,128,129,129,130,130,130,130,130,129,128,128,127,127,128,127,129,
129,130,130,131,129,129,130,128,128,128,127,128,128,128,129,128,129,129,129,
129,129,129,128,128,128,128,128,128,129,129,129,129,129,129,129,129,128,127,
128,127,128,129,127,128,128,128,128,128,129,128,128,129,128,128,129,129,128,
128,129,129,128,129,128,128,128,128,128,128,128,128,128,128,128,128,128,127,
128,127,128,127,127,127,127,127,127,127,128,127,127,127,127,127,127,127,127,
127,128,127,127,127,127,127,127,127,127,127,127,127,126,127,127,126,127,127,
128,127,127,128,127,128,128,127,127,128,128,128,128,129,128,128,128,128,129,
129,129,128,128,129,129,129,128,129,129,128,129,129,128,129,128,129,128,129,
129,128,128,128,128,129,129,128,129,129,128,129,129,129,128,129,128,128,129,
129,128,129,128,129,129,128,128,129,129,129,129,128,128,129,128,129,129,129,
129,128,129,128,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,
128,129,128,129,128,128,129,128,129,129,128,128,128,128,128,128,128,128,128,
129,128,128,128,129,128,128,128,127,128,128,128,128,128,127,127,127,127,127,
127,128,128,128,127,128,127,127,127,127,127,127,127,128,127,127,127,127,127,
127,127,126,127,127,127,127,127,127,127,127,127,127,128,127,127,128,127,128,
128,128,128,128,128,128,128,128,128,129,129,128,128,128,129,129,129,129,128,
129,128,129,128,128,129,129,128,128,129,129,129,129,129,129,129,128,129,129,
128,129,128,129,128,129,129,128,129,129,129,129,129,129,129,129,129,129,128,
128,129,129,129,129,129,128,129,128,129,129,128,128,129,129,128,129,128,129,
128,128,128,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,129,
129,128,128,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,127,
128,127,128,128,127,128,127,127,127,127,127,127,128,127,127,127,127,127,128,
127,127,127,127,127,127,127,127,126,127,126,127,126,127,127,127,127,127,127,
127,127,127,127,127,128,128,128,128,128,128,127,128,128,128,128,128,128,129,
129,128,128,128,129,128,128,128,129,129,129,128,129,128,128,129,128,128,129,
129,129,129,129,129,129,128,129,129,129,129,129,129,128,129,128,129,129,128,
128,129,129,129,129,129,129,129,128,128,128,128,128,129,129,128,129,128,128,
129,129,128,128,128,128,128,128,128,128,128,129,128,128,128,128,128,128,128,
129,129,128,128,129,128,128,128,128,128,128,128,128,128,128,128,128,128,128,
129,128,128,128,128,128,127,127,127,127,127,127,127,127,127,128,127,126,127,
127,127,127,127,127,127,127,127,127,127,127,127,127,127,127,126,127,127,127,
127,127,126,127,127,127,127,128,127,127,128,127,128,128,128,128,127,127,128,
128,128,128,128,128,128,128,129,128,128,129,129,129,128,128,128,129,129,129,
128,128,128,129,129,128,129,128,128,129,128,129,128,129,128,128,129,128,128,
128,129,128,129,129,129,129,128,129,128,128,128,128,128,128,129,129,129,129,
129,129,129,128,128,129,129,129,129,129,128,128,128,129,128,128,128,128,128,
128,128,128,128,128,128,128,129,129,128,128,128,128,128,129,128,128,128,128,
129,129,128,128,129,128,128,128,128,128,128,128,127,128,128,127,127,127,127,
127,127,127,127,127,127,127,128,127,128,127,127,127,127,127,127,127,127,127,
127,127,127,127,127,127,127,127,127,127,127,127,126,127,127,127,127,127,127,
127,128,128,128,128,128,128,128,128,127,128,128,129,128,128,129,129,128,129,
129,129,128,128,128,129,128,129,129,129,128,128,128,128,128,128,128,125,123,
116,156,127,104,144,142,115,118,141,134,118,125,142,131,117,132,141,121,121,
138,131,121,116,131,177,77,84,212,140,66,143,173,116,95,142,155,116,103,
151,150,100,116,165,122,97,151,142,104,128,151,115,121,137,129,105,122,151,
127,118,122,150,130,109,131,149,125,109,141,142,112,119,145,129,115,133,137,
126,123,132,135,124,123,134,130,122,127,134,125,123,130,130,123,127,130,128,
125,129,128,128,126,127,130,127,123,130,129,124,124,128,131,123,126,131,126,
126,127,128,128,126,125,128,128,125,128,130,127,127,129,129,126,129,129,128,
128,129,129,128,127,128,130,128,127,130,129,127,129,130,127,128,129,128,127,
127,128,128,127,127,129,127,127,128,128,127,128,128,128,127,127,129,127
};

// these will be offsets into the waves.tar file:
static uint32_t offsets[17] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

// these will be the file sizes in the waves.tar file:
static int wavsize[17] = {
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0
};

static const char *words[17] PROGMEM = {
    "traffic",
    "high",
    "low",
    "level",
    "danger",
    "nine",
    "ten",
    "eleven",
    "ahead",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
};

// public
int num_wav_files = 0;

// public
void clear_waves()
{
    for (int i=0; i<17; i++) {
       offsets[i] = 0;
       wavsize[i] = 0;
    }
    num_wav_files = 0;
}

static uint32_t wordoffset = 0;
static int wordsize = 0;
static const uint8_t *defaultp = NULL;
static File tarfile;

// public
bool word2wav(const char *word) {

    if (wordoffset > 0)
        tarfile.close();
    wordoffset = 0;
    wordsize = 0;
    defaultp = NULL;

    if (num_wav_files == 0) {
        Serial.println("word2wav: no WAV files");
        defaultp = defaultwav;
        wordsize = DEFAULTSIZE;
        return false;
    }

    for (int i=0; i<17; i++) {
        if (strcmp(word,words[i])==0 && offsets[i] > 0) {
            tarfile = SPIFFS.open("/waves.tar", "r");
            if (!tarfile) {
                Serial.println(F("Failed to open waves.tar"));
                break;
            }
            uint32_t offset = offsets[i];
            if (! tarfile.seek(offset, SeekSet)) {
                Serial.println(F("Failed to fseek to wav position"));
                tarfile.close();
                break;
            }
            wordoffset = offset;
            wordsize = wavsize[i];
            Serial.printf("word2wav: '%s' found -> %d bytes\n", word, wordsize);
            return true;
        }
    }

    Serial.printf("word2wav: '%s' not found\n", word);
    defaultp = defaultwav;
    wordsize = DEFAULTSIZE;
    return false;
}

// public: read one byte from WAV file
//  - at EOF returns false
int read_wav_byte(uint8_t &data)
{
    int rval = 0;

    if (wordsize <= 0)
        return 0;

    if (defaultp != NULL) {   // playing the default built-in word
        data = *defaultp++;
        --wordsize;
        rval = -1;
    } else if (wordoffset > 0) {    // playing a file
        if (tarfile.available()) {
            data = tarfile.read();
            --wordsize;
            rval = 1;
        } else {
            wordsize = 0;
        }
    } else {
        wordsize = 0;
    }

    if (wordsize <= 0) {
        if (wordoffset > 0)
            tarfile.close();
        wordoffset = 0;
        wordsize = 0;
        defaultp = NULL;
    }

    return rval;
}


/**********************************************************/

// Code adapted from untar.c by Tim Kientzle:

/* Parse an octal number, ignoring leading and trailing nonsense. */
static int
parseoct(const char *p, size_t n)
{
    int i = 0;

    while ((*p < '0' || *p > '7') && n > 0) {
        ++p;
        --n;
    }
    while (*p >= '0' && *p <= '7' && n > 0) {
        i *= 8;
        i += *p - '0';
        ++p;
        --n;
    }
    return (i);
}

/* Returns true if this is 512 zero bytes. */
static int
is_end_of_archive(const char *p)
{
    int n;
    for (n = 511; n >= 0; --n)
        if (p[n] != '\0')
            return (0);
    return (1);
}

/* Verify the tar checksum. */
static int
verify_checksum(const char *p)
{
    int n, u = 0;
    for (n = 0; n < 512; ++n) {
        if (n < 148 || n > 155)
            /* Standard tar checksum adds unsigned bytes. */
            u += ((unsigned char *)p)[n];
        else
            u += 0x20;

    }
    return (u == parseoct(p + 148, 8));
}

typedef struct wavProperties_s {
    uint32_t chunkID;
    uint32_t chunkSize;
    uint16_t audioFormat;
    uint16_t numChannels;
    uint32_t sampleRate;
    uint32_t byteRate;
    uint16_t blockAlign;
    uint16_t bitsPerSample;
} wavProperties_t;

/* parse waves.tar in SPIFFS, store found offsets */
// public
int parse_wav_tar()
{
    char buff[512];
    char name[128];
    size_t bytes_read;
    uint32_t offset = 0;
    uint32_t filesize, foundfilesize, foundoffset;
    bool is_a_wav_file;

    clear_waves();

    if (!SPIFFS.begin(true)) {
        Serial.println(F("An Error has occurred while mounting SPIFFS"));
        return 0;
    }

    if (!SPIFFS.exists("/waves.tar")) {
        Serial.println(F("waves.tar not present in SPIFFS"));
        return 0;
    }

    File tarfile = SPIFFS.open("/waves.tar", "r");
    if (!tarfile) {
        Serial.println(F("Failed to open waves.tar"));
        return 0;
    }      

    Serial.println(F("Parsing waves.tar..."));

    while (true) {
        bytes_read = tarfile.read((uint8_t *)buff, 512);
        offset += 512;
        if (bytes_read < 512) {
            Serial.printf("Short read TAR header: got %d bytes\n",
                (int)bytes_read);
            tarfile.close();
            return num_wav_files;
        }
        if (is_end_of_archive(buff)) {
            Serial.printf("Found %d wav files\n", num_wav_files);
            tarfile.close();
            return num_wav_files;
        }
        if (!verify_checksum(buff)) {
            Serial.println(F("Checksum failure"));
            tarfile.close();
            return num_wav_files;
        }
        filesize = parseoct(buff + 124, 12);
        switch (buff[156]) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
            break;
        default:
            Serial.printf("... file %s ... ", buff);
            is_a_wav_file = true;
            strcpy(name,buff);
            char *p = strrchr(name,'.');
            // each file must be called something.wav
            if (p == NULL)
                is_a_wav_file = false;
            else if (strcmp(p+1,"wav") && strcmp(p+1,"WAV"))
                is_a_wav_file = false;
            else
                *p = '\0';     // drop the file extension
            if (offset != tarfile.position())
                Serial.println(F("Warning: offset != file position"));
            foundoffset = tarfile.position();
            foundfilesize = filesize;
            if (filesize < 1000 || filesize > 32000)   // these should be small files
                is_a_wav_file = false;
            if (is_a_wav_file == false)
                break;
            // read the first file block and examine the WAV header
            bytes_read = tarfile.read((uint8_t *)buff, 512);
            offset += 512;
            if (bytes_read < 512) {
                Serial.printf("Short read WAV header: got %d bytes\n",
                    (int)bytes_read);
                tarfile.close();
                return num_wav_files;
            }
            if (filesize < 512)
                bytes_read = filesize;
            filesize -= bytes_read;
            // must be mono 8-bit PCM file with sample rate 8000
            wavProperties_t *wp = (wavProperties_t *) &buff[12];
            if (wp->audioFormat != 1
            ||  wp->numChannels != 1
            ||  wp->sampleRate != 8000
            ||  wp->bitsPerSample != 8)
                is_a_wav_file = false;
            break;
        }
        // read through (and ignore) the rest of the WAV data
        while (filesize > 0) {
            bytes_read = tarfile.read((uint8_t *)buff, 512);
            offset += 512;
            if (bytes_read < 512) {
                Serial.printf("Short read WAV data: got %d bytes\n",
                    (int)bytes_read);
                tarfile.close();
                return num_wav_files;
            }
            if (filesize < 512)
                bytes_read = filesize;
            filesize -= bytes_read;
        }
        int i;
        if (is_a_wav_file) {
            for (i=0; i<17; i++) {
                if (strcmp(name,words[i])==0) {
                    Serial.println(F("matched"));
                    ++num_wav_files;
                    // skip WAV header and also drop last 40 bytes
                    wavsize[i] = (int) foundfilesize - 84;
                    offsets[i] = foundoffset + 44;
                    break;
                }
            }
            if (i==17)  // not found
                Serial.println(F("not matched"));
        }
    }
    tarfile.close();
    return num_wav_files;
}

/**********************************************************/

#endif
#endif
