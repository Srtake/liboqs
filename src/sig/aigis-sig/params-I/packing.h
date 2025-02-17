#ifndef PACKING_H
#define PACKING_H

#include "polyvec.h"

void pack_pk_param_i(unsigned char pk[PK_SIZE_PACKED],
             const unsigned char rho[SEEDBYTES], const polyveck *t1);
void pack_sk_param_i(unsigned char sk[SK_SIZE_PACKED],
             const unsigned char buf[2*SEEDBYTES + CRHBYTES],
             const polyvecl *s1,
             const polyveck *s2,
             const polyveck *t0);
void pack_sig_param_i(unsigned char sm[SIG_SIZE_PACKED],
              const polyvecl *z, const polyveck *h, const poly *c);

void unpack_pk_param_i(unsigned char rho[SEEDBYTES], polyveck *t1,
               const unsigned char sk[SK_SIZE_PACKED]);
void unpack_sk_param_i(unsigned char buf[2*SEEDBYTES + CRHBYTES],
               polyvecl *s1,
               polyveck *s2,
               polyveck *t0,
               const unsigned char sk[SK_SIZE_PACKED]);
void unpack_sig_param_i(polyvecl *z, polyveck *h, poly *c,
                const unsigned char sm[SIG_SIZE_PACKED]);

#endif
