#ifndef POLYVEC_H
#define POLYVEC_H

#include <stdint.h>
#include "params.h"
#include "poly.h"

/* Vectors of polynomials of length L */
typedef struct {
  poly vec[PARAM_L];
} polyvecl;

void polyvecl_freeze_param_iib(polyvecl *v);
void polyvecl_freeze2q_param_iib(polyvecl *v);
void polyvecl_freeze4q_param_iib(polyvecl *v);

void polyvecl_add_param_iib(polyvecl *w, const polyvecl *u, const polyvecl *v);

void polyvecl_ntt_param_iib(polyvecl *v);
void polyvecl_pointwise_acc_invmontgomery_param_iib(poly *w,
                                          const polyvecl *u,
                                          const polyvecl *v);

int polyvecl_chknorm_param_iib(const polyvecl *v, uint32_t B);



/* Vectors of polynomials of length K */
typedef struct {
  poly vec[PARAM_K];
} polyveck;

void polyveck_freeze_param_iib(polyveck *v);
void polyveck_freeze2q_param_iib(polyveck *v);
void polyveck_freeze4q_param_iib(polyveck *v);

void polyveck_add_param_iib(polyveck *w, const polyveck *u, const polyveck *v);
void polyveck_sub_param_iib(polyveck *w, const polyveck *u, const polyveck *v);
void polyveck_neg_param_iib(polyveck *v);
void polyveck_shiftl_param_iib(polyveck *v, unsigned int k);

void polyveck_ntt_param_iib(polyveck *v);
void polyveck_invntt_montgomery_param_iib(polyveck *v);

int polyveck_chknorm_param_iib(const polyveck *v, uint32_t B);

void polyveck_power2round_param_iib(polyveck *v1, polyveck *v0, const polyveck *v);
void polyveck_decompose_param_iib(polyveck *v1, polyveck *v0, const polyveck *v);
unsigned int polyveck_make_hint_param_iib(polyveck *h,
                                const polyveck *u,
                                const polyveck *v);
void polyveck_use_hint_param_iib(polyveck *w, const polyveck *v, const polyveck *h);

#endif
