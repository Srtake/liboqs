#ifndef API_H
#define API_H

#include "params.h"

#define SIG_SECRETKEYBYTES SK_SIZE_PACKED
#define SIG_PUBLICKEYBYTES PK_SIZE_PACKED
#define SIG_BYTES SIG_SIZE_PACKED

#define SIG_ALGNAME "Aigis-sig"

            
int msig_keygen_param_i(unsigned char *pk, unsigned char *sk);
                   
int msig_sign_param_i(unsigned char *sk, 
                   unsigned char *m, unsigned long long mlen, 
                   unsigned char *sm, unsigned long long *smlen);                     

int msig_verf_param_i(unsigned char *pk,
                   unsigned char *sm, unsigned long long smlen,
                   unsigned char *m, unsigned long long mlen);
#endif
