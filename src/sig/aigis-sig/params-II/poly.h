#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "params.h"
#include "fips202.h"

typedef __declspec(align(32)) struct {
  uint32_t coeffs[PARAM_N];
} poly;

void poly_freeze2q(poly *a);
void poly_freeze4q(poly *a);
void poly_barrat_reduce(poly *a);
void poly_decompose(poly *r1,poly *r0, const poly *a);
void poly_power2round(poly *r1,poly *r0, const poly *a);
uint32_t poly_make_hint(poly *h, const poly *a, const poly *b);

void poly_add(poly *c, const poly *a, const poly *b);
void poly_sub(poly *c, const poly *a, const poly *b);
void poly_neg(poly *a);
void poly_shiftl(poly *a, unsigned int k);

void poly_ntt(poly *a);
void poly_invntt_montgomery(poly *a);
void poly_pointwise_invmontgomery(poly *c, const poly *a, const poly *b);

int  poly_chknorm(const poly *a, uint32_t B);
void poly_uniform(poly *a, unsigned char *buf);
void poly_uniform_eta1(poly *a,
                      const unsigned char seed[SEEDBYTES],
                      unsigned char nonce);
void poly_uniform_eta1_3x(poly *a0,
                          poly *a1,
                          poly *a2,
                          const unsigned char seed[SEEDBYTES],
                          unsigned char nonce0,
                          unsigned char nonce1,
                          unsigned char nonce2);
void poly_uniform_eta1_4x(poly *a0,
                         poly *a1,
                         poly *a2,
                         poly *a3,
                         const unsigned char seed[SEEDBYTES], 
                         unsigned char nonce0,
                         unsigned char nonce1,
                         unsigned char nonce2,
                         unsigned char nonce3);

void poly_uniform_eta2(poly *a,
                      const unsigned char seed[SEEDBYTES],
                      unsigned char nonce);
void poly_uniform_eta2_4x(poly *a0,
                         poly *a1,
                         poly *a2,
                         poly *a3,
                         const unsigned char seed[SEEDBYTES], 
                         unsigned char nonce0,
                         unsigned char nonce1,
                         unsigned char nonce2,
                         unsigned char nonce3);
void poly_uniform_eta2_2x(poly *a0,
	poly *a1,
	const unsigned char seed[SEEDBYTES],
	unsigned char nonce0,
	unsigned char nonce1);
void poly_uniform_gamma1m1(poly *a,
                           const unsigned char seed[SEEDBYTES + CRHBYTES],
                           uint16_t nonce);
void poly_uniform_gamma1m1_3x(poly *a0,
                              poly *a1,
                              poly *a2,
                              const unsigned char seed[SEEDBYTES + CRHBYTES],
                              uint16_t nonce0,
                              uint16_t nonce1,
                              uint16_t nonce2);
void poly_uniform_gamma1m1_4x(poly *a0,
                              poly *a1,
                              poly *a2,
                              poly *a3,
                              const unsigned char seed[SEEDBYTES + CRHBYTES],
                              uint16_t nonce0,
                              uint16_t nonce1,
                              uint16_t nonce2,
                              uint16_t nonce3);                        
void polyeta1_pack(unsigned char *r, const poly *a);
void polyeta1_unpack(poly *r, const unsigned char *a);
void polyeta2_pack(unsigned char *r, const poly *a);
void polyeta2_unpack(poly *r, const unsigned char *a);

void polyt1_pack(unsigned char *r, const poly *a);
void polyt1_unpack(poly *r, const unsigned char *a);

void polyt0_pack(unsigned char *r, const poly *a);
void polyt0_unpack(poly *r, const unsigned char *a);

void polyz_pack(unsigned char *r, const poly *a);
void polyz_unpack(poly *r, const unsigned char *a);

void polyw1_pack(unsigned char *r, const poly *a);
#endif
