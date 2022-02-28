#ifndef NTT_H
#define NTT_H

#include <stdint.h>
#include "params.h"



void ntt_param_iib(uint32_t p[PARAM_N]);
void invntt_param_iib(uint32_t p[PARAM_N]);
#endif
