#ifndef _US_ICAO_H_
#define _US_ICAO_H_

#include <stddef.h>
#include <stdint.h>

uint32_t us_icao_n2i(const char * src);
size_t   us_icao_i2n(char * dst, size_t sz, uint32_t icao); 


static inline int is_us_reg(uint32_t icao) {
    return (icao > 0xA00000) && (icao < 0xADF7C8);
}

#endif
