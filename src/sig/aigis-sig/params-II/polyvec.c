#include <stdint.h>
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "ntt.h"


void polyvecl_freeze2q_param_ii(polyvecl *v) {
    unsigned int i;
    
    for(i = 0; i < PARAM_L; ++i)
        poly_freeze2q_param_ii(&v->vec[i]);
}

void polyvecl_freeze4q_param_ii(polyvecl *v) {
    unsigned int i;  
    for(i = 0; i < PARAM_L; ++i)
        poly_freeze4q_param_ii(&v->vec[i]);
}

void polyvecl_add_param_ii(polyvecl *w, const polyvecl *u, const polyvecl *v) {
  unsigned int i;

  for(i = 0; i < PARAM_L; ++i)
    poly_add_param_ii(w->vec+i, u->vec+i, v->vec+i);
}

void polyvecl_ntt_param_ii(polyvecl *v) {
  unsigned int i;

  for(i = 0; i < PARAM_L; ++i)
    poly_ntt_param_ii(v->vec+i);
}

void polyvecl_pointwise_acc_invmontgomery_param_ii(poly *w,
                                          const polyvecl *u,
                                          const polyvecl *v) 
{
  unsigned int i;
  poly t;

  poly_pointwise_invmontgomery_param_ii(w, u->vec+0, v->vec+0);

  for(i = 1; i < PARAM_L; ++i) {
    poly_pointwise_invmontgomery_param_ii(&t, u->vec+i, v->vec+i);
    poly_add_param_ii(w, w, &t);
  }
  poly_barrat_reduce_param_ii(w);
}

int polyvecl_chknorm_param_ii(const polyvecl *v, uint32_t bound)  {
  unsigned int i;
  int ret = 0;

  for(i = 0; i < PARAM_L; ++i)
    ret |= poly_chknorm_param_ii(v->vec+i, bound);

  return ret;
}

void polyveck_freeze2q_param_ii(polyveck *v)  {
    unsigned int i;
    for(i = 0; i < PARAM_K; ++i)
        poly_freeze2q_param_ii(&v->vec[i]);
}

void polyveck_freeze4q_param_ii(polyveck *v)  {
    unsigned int i;
    for(i = 0; i < PARAM_K; ++i)
        poly_freeze4q_param_ii(&v->vec[i]);
}

void polyveck_add_param_ii(polyveck *w, const polyveck *u, const polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_add_param_ii(w->vec+i, u->vec+i, v->vec+i);
}

void polyveck_sub_param_ii(polyveck *w, const polyveck *u, const polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_sub_param_ii(w->vec+i, u->vec+i, v->vec+i);
}

void polyveck_neg_param_ii(polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_neg_param_ii(v->vec+i);
}

void polyveck_shiftl_param_ii(polyveck *v, unsigned int k) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_shiftl_param_ii(v->vec+i, k);
}

void polyveck_ntt_param_ii(polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_ntt_param_ii(v->vec+i);
}

void polyveck_invntt_montgomery_param_ii(polyveck *v) {
  unsigned int i;

  for(i = 0; i < PARAM_K; ++i)
    poly_invntt_montgomery_param_ii(v->vec+i);
}

int polyveck_chknorm_param_ii(const polyveck *v, uint32_t bound) {
  unsigned int i;
  int ret = 0;

  for(i = 0; i < PARAM_K; ++i)
    ret |= poly_chknorm_param_ii(v->vec+i, bound);

  return ret;
}

void polyveck_power2round_param_ii(polyveck *v1, polyveck *v0, const polyveck *v) {
  unsigned int i;
  for(i = 0; i < PARAM_K; ++i)
  	poly_power2round_param_ii(&v1->vec[i],&v0->vec[i], &v->vec[i]);
}

void polyveck_decompose_param_ii(polyveck *v1, polyveck *v0, const polyveck *v) {
  unsigned int i;
  for(i = 0; i < PARAM_K; ++i)
    poly_decompose_param_ii(&v1->vec[i],&v0->vec[i],&v->vec[i]);
}

unsigned int polyveck_make_hint_param_ii(polyveck *h,
                                const polyveck *u,
                                const polyveck *v)
{
  unsigned int i,s = 0;
  for(i = 0; i < PARAM_K; ++i)
      s+=poly_make_hint_param_ii(&h->vec[i],&u->vec[i],&v->vec[i]);
  
  return s;
}

void polyveck_use_hint_param_ii(polyveck *w, const polyveck *u, const polyveck *h) {
  unsigned int i, j;
  poly v1,v0;
  for(i = 0; i < PARAM_K; ++i)
  {
   poly_decompose_param_ii(&v1,&v0,&u->vec[i]);
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
