#include "us_icao.h"

/*
 * US registration number is coded positionally in aircraft ICAO ID.
 * Registration number is "N" followed by ont to three  digits prefix
 * (first digit nonzero), followed by optional one or two symbol
 * alphanumeric suffix. Letters I and O are excluded, and digits cannot
 * follow letters. N-number is at least 2 and at most 6 charachers,
 * including 'N'.
 *
 * Details of the encoding can be found elsewhere, but for a brief
 * desription of constants here:
 * 25 - number of codes for the suffix position when it follows
 *      a letter (alphabet without I and O, plus 'empty' code)
 * 35 - number of codes in the suffix position when it follows
 *      a digit (alphabet without I and O, digits and 'empty')
 * 601 - number of possible letter-only suffixes (including empty suffix)
 * 951 - scaler for position 3 (number of all possible alphanumeric suffixes)
 * 10111 - scaler for position 2 (number of combinations past 2nd position)
 * 101711 - scaler for the 1st position.
 *
 */

// N-number suffix codes: letters \ {I,O} ++ digits
static const char tab[] = "ABCDEFGHJKLMNPQRSTUVWXYZ0123456789";

// Scale coefficients for prefix positions
static const uint32_t mpy[] = {101711, 10111, 951, 35};

// Computing symbol position in the table
static inline int anumpos(char c) {
  return (c < 'A') ? (c - '0' + 24) :
    (c < 'I') ? (c - 'A') :
    (c < 'O') ? (c - 'B') : (c - 'C');
}
static inline int numpos(char c) {
  return c - '0';
}


/**
 * @brief Convert US aircraft registration number to ICAO ID
 * 
 * @param src A null-terminated string with N-number
 * @return icao number
 */
uint32_t us_icao_n2i(const char * src)
{
    int sum = 0xA00001 - 101711 - 601;

    if (src[0] != 'N') return 0;

    const char * p = src+1;
  
    for (int i = 0; i < 4; i++) {
      if (*p == '\0') break;
      char a = *p++;
      if (a < 'A') {
        sum += numpos(a) * mpy[i] + 601;
      }
      else { // letter-only suffix
	sum += 25 * anumpos(a) + 1;
	break;
      }
    }
    if (*p != '\0') {
      char a = *p++;
      sum += anumpos(a) + 1;
    }
    
    return (*p == '\0') ? sum : 0;
}

/**
 * @brief Convert aircraft ICAO number to US registration number.
 * 
 * @param dst Buffer to write registration number as null-terminated string
 * @param sz Buffer size. Should be at least 7 bytes.
 * @param icao Aircraft ICAO Id.
 * @return registration number length (between 2 and 6)
 */
size_t us_icao_i2n(char * dst, size_t sz, uint32_t icao)
{
  char * p = dst+1;

  if ((sz < 7) || 
      (icao <  0xA00001) ||
      (icao >= 0xA00001 + 9 * 101711)) goto FAIL;
  
  dst[0] = 'N';
  icao = icao - 0xA00001 + 101711 + 601;

  for (int i = 0; i < 4; i++) {
    if (icao >= 601) {
      icao -= 601;
      *p++ = '0' + icao / mpy[i];
      icao = icao % mpy[i];
    }      
    else { // Letter-only suffix, not in the last position
      if (icao > 0) {
	      icao--;
	      *p++ = tab[icao / 25];
	      icao = icao % 25;
      }
      break;
    }
  }
  // last position
  if (icao > 0) {
    *p++ = tab[icao-1];
  }
  
  *p = '\0';
  return (p - dst);

FAIL:
  if (sz > 0) dst[0] = '\0';
  return 0;
}
