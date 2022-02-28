#ifndef SIGN_H
#define SIGN_H

#include "params.h"
#include "poly.h"
#include "polyvec.h"

void expand_mat_param_i(polyvecl *mat, const unsigned char rho[SEEDBYTES]);
void challenge_param_i(poly *c, const unsigned char mu[CRHBYTES],
               const polyveck *w1);

int msig_keygen_param_i(unsigned char *pk, unsigned char *sk);

int msig_sign_param_i(unsigned char *sk, 
                   unsigned char *m, unsigned long long mlen, 
                   unsigned char *sm, unsigned long long *smlen);                     

int msig_verf_param_i(unsigned char *pk,
                   unsigned char *sm, unsigned long long smlen,
                   unsigned char *m, unsigned long long mlen);

#endif
