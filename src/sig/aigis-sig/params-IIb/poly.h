#ifndef POLY_H
#define POLY_H

#include <stdint.h>
#include "params.h"
#include "fips202.h"

typedef __declspec(align(32)) struct {
  uint32_t coeffs[PARAM_N];
} poly;

void poly_freeze2q_param_iib(poly *a);
void poly_freeze4q_param_iib(poly *a);
void poly_barrat_reduce_param_iib(poly *a);
void poly_decompose_param_iib(poly *r1,poly *r0, const poly *a);
void poly_power2round_param_iib(poly *r1,poly *r0, const poly *a);
uint32_t poly_make_hint_param_iib(poly *h, const poly *a, const poly *b);

void poly_add_param_iib(poly *c, const poly *a, const poly *b);
void poly_sub_param_iib(poly *c, const poly *a, const poly *b);
void poly_neg_param_iib(poly *a);
void poly_shiftl_param_iib(poly *a, unsigned int k);

void poly_ntt_param_iib(poly *a);
void poly_invntt_montgomery_param_iib(poly *a);
void poly_pointwise_invmontgomery_param_iib(poly *c, const poly *a, const poly *b);

int  poly_chknorm_param_iib(const poly *a, uint32_t B);
void poly_uniform_param_iib(poly *a, unsigned char *buf);
void poly_uniform_eta1_param_iib(poly *a,
                      const unsigned char seed[SEEDBYTES],
                      unsigned char nonce);
void poly_uniform_eta1_3x_param_iib(poly *a0,
                          poly *a1,
                          poly *a2,
                          const unsigned char seed[SEEDBYTES],
                          unsigned char nonce0,
                          unsigned char nonce1,
                          unsigned char nonce2);
void poly_uniform_eta1_4x_param_iib(poly *a0,
                         poly *a1,
                         poly *a2,
                         poly *a3,
                         const unsigned char seed[SEEDBYTES], 
                         unsigned char nonce0,
                         unsigned char nonce1,
                         unsigned char nonce2,
                         unsigned char nonce3);

void poly_uniform_eta2_param_iib(poly *a,
                      const unsigned char seed[SEEDBYTES],
                      unsigned char nonce);
void poly_uniform_eta2_4x_param_iib(poly *a0,
                         poly *a1,
                         poly *a2,
                         poly *a3,
                         const unsigned char seed[SEEDBYTES], 
                         unsigned char nonce0,
                         unsigned char nonce1,
                         unsigned char nonce2,
                         unsigned char nonce3);
void poly_uniform_eta2_2x_param_iib(poly *a0,
	poly *a1,
	const unsigned char seed[SEEDBYTES],
	unsigned char nonce0,
	unsigned char nonce1);
void poly_uniform_gamma1m1_param_iib(poly *a,
                           const unsigned char seed[SEEDBYTES + CRHBYTES],
                           uint16_t nonce);
void poly_uniform_gamma1m1_3x_param_iib(poly *a0,
                              poly *a1,
                              poly *a2,
                              const unsigned char seed[SEEDBYTES + CRHBYTES],
                              uint16_t nonce0,
                              uint16_t nonce1,
                              uint16_t nonce2);
void poly_uniform_gamma1m1_4x_param_iib(poly *a0,
                              poly *a1,
                              poly *a2,
                              poly *a3,
                              const unsigned char seed[SEEDBYTES + CRHBYTES],
                              uint16_t nonce0,
                              uint16_t nonce1,
                              uint16_t nonce2,
                              uint16_t nonce3);                        
void polyeta1_pack_param_iib(unsigned char *r, const poly *a);
void polyeta1_unpack_param_iib(poly *r, const unsigned char *a);
void polyeta2_pack_param_iib(unsigned char *r, const poly *a);
void polyeta2_unpack_param_iib(poly *r, const unsigned char *a);

void polyt1_pack_param_iib(unsigned char *r, const poly *a);
void polyt1_unpack_param_iib(poly *r, const unsigned char *a);

void polyt0_pack_param_iib(unsigned char *r, const poly *a);
void polyt0_unpack_param_iib(poly *r, const unsigned char *a);

void polyz_pack_param_iib(unsigned char *r, const poly *a);
void polyz_unpack_param_iib(poly *r, const unsigned char *a);

void polyw1_pack_param_iib(unsigned char *r, const poly *a);
#endif
