#ifndef __trng_h__
#define __trng_h__
#include <trng.h>

void TrngInitialize(void);

int Trng0GetSource(uint8_t *outAddr, uint32_t reqBytes);

int Trng0GetSourceFast(uint8_t *outAddr, uint32_t reqBytes);

#endif
