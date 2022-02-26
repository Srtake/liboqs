#include <stdint.h>
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "ntt.h"


void polyvecl_freeze2q(polyvecl *v) {
    unsigned int i;
    
    for(i = 0; i < PARAM_L; ++i)
        poly_freeze2q(&v->vec[i]);
}

void polyvecl_freeze4q(polyvecl *v) {
    unsigned int i;  
    for(i = 0; i < PARAM_L; ++i)
        poly_freeze4q(&v->vec[i]);
}

void polyvecl_add(polyvecl *w, const polyvecl *u, const polyvecl *v) {
  unsigned int i;

  for(i = 0; i < PARAM_L; ++i)
    poly_add(w->vec+i, u->vec+i, v->vec+i);
}

void polyvecl_ntt(polyvecl *v) {
  unsigned int i;

  for(i = 0; i < PARAM_L; ++i)
    poly_ntt(v->vec+i);
}

void polyvecl_pointwise_acc_invmontgomery(poly *w,
                                          const polyvecl *u,
                                          const polyvecl *v) 
{
  unsigned int i;
  poly t;

  poly_pointwise_invmontgomery(w, u->vec+0, v->vec+0);

  for(i = 1; i < PARAM_L; ++i) {
    poly_pointwise_invmontgomery(&t, u->vec+i, v->vec+i);
    poly_add(w, w, &t);
  }
  poly_barrat_reduce(w);
}

int polyvecl_chknorm(const polyvecl *v, uint32_t bound)  {
  unsigned int i;
  int ret = 0;

  for(i = 0; i < PARAM_L; ++i)
    ret |= poly_chknorm(v->vec+i, bound);

  return ret;
}

void polyveck_freeze2q(polyveck *v)  {
    unsigned int i;
    for(i = 0; i < PARAM_K; ++i)
        poly_freeze2q(&v->vec[i]);
}

void polyveck_freeze4q(polyveck *v)  {
    unsigned int i;
    for(i = 0; i < PARAM_K; ++i)
        poly_freeze4q(&v->vec[i]);
}

void polyveck_add(polyveck *w, const polyveck *u, const polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_add(w->vec+i, u->vec+i, v->vec+i);
}

void polyveck_sub(polyveck *w, const polyveck *u, const polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_sub(w->vec+i, u->vec+i, v->vec+i);
}

void polyveck_neg(polyveck *v) { 
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_neg(v->vec+i);
}

void polyveck_shiftl(polyveck *v, unsigned int k) { 
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_shiftl(v->vec+i, k);
}

void polyveck_ntt(polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_ntt(v->vec+i);
}

void polyveck_invntt_montgomery(polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_invntt_montgomery(v->vec+i);
}

int polyveck_chknorm(const polyveck *v, uint32_t bound) {
  unsigned int i;
  int ret = 0;

  for(i = 0; i < PARAM_K; ++i)
    ret |= poly_chknorm(v->vec+i, bound);

  return ret;
}

void polyveck_power2round(polyveck *v1, polyveck *v0, const polyveck *v) {
  unsigned int i;
  for(i = 0; i < PARAM_K; ++i)
  	poly_power2round(&v1->vec[i],&v0->vec[i], &v->vec[i]);
}

void polyveck_decompose(polyveck *v1, polyveck *v0, const polyveck *v) {
  unsigned int i;
  for(i = 0; i < PARAM_K; ++i)
    poly_decompose(&v1->vec[i],&v0->vec[i],&v->vec[i]);
}

unsigned int polyveck_make_hint(polyveck *h,
                                const polyveck *u,
                                const polyveck *v)
{
  unsigned int i,s = 0;
  for(i = 0; i < PARAM_K; ++i)
      s+=poly_make_hint(&h->vec[i],&u->vec[i],&v->vec[i]);
  
  return s;
}

void polyveck_use_hint(polyveck *w, const polyveck *u, const polyveck *h) {
  unsigned int i, j;
  poly v1,v0;
  for(i = 0; i < PARAM_K; ++i)
  {
   poly_decompose(&v1,&v0,&u->vec[i]);
    for(j = 0; j < PARAM_N; ++j)
    {
     if(h->vec[i].coeffs[j] == 0)
     w->vec[i].coeffs[j]=v1.coeffs[j];
  else if(v0.coeffs[j] > PARAM_Q)
    w->vec[i].coeffs[j] = (v1.coeffs[j] == (PARAM_Q - 1)/ALPHA - 1) ? 0 : v1.coeffs[j] + 1;
  else
    w->vec[i].coeffs[j] = (v1.coeffs[j] == 0) ? (PARAM_Q - 1)/ALPHA - 1 : v1.coeffs[j] - 1;
    }
  }
}
