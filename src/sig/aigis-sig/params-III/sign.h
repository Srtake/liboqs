#ifndef SIGN_H
#define SIGN_H

#include "params.h"
#include "poly.h"
#include "polyvec.h"

void expand_mat(polyvecl *mat, const unsigned char rho[SEEDBYTES]);
void challenge(poly *c, const unsigned char mu[CRHBYTES],
               const polyveck *w1);

int msig_keygen(unsigned char *pk, unsigned char *sk);

int msig_sign(unsigned char *sk, 
                   unsigned char *m, unsigned long long mlen, 
                   unsigned char *sm, unsigned long long *smlen);                     

int msig_verf(unsigned char *pk,
                   unsigned char *sm, unsigned long long smlen,
                   unsigned char *m, unsigned long long mlen);

#endif
