
#include "params.h"
#include "poly.h"
#include "polyvec.h"
#include "packing.h"

/*************************************************
* pack the public key pk, 
* where pk = rho|t1
**************************************************/
void pack_pk_param_iib(unsigned char pk[PK_SIZE_PACKED],
             const unsigned char rho[SEEDBYTES],
             const polyveck *t1)
{
  unsigned int i;

  for(i = 0; i < SEEDBYTES; ++i)
    pk[i] = rho[i];
  pk += SEEDBYTES;

  for(i = 0; i < PARAM_K; ++i)
    polyt1_pack_param_iib(pk + i*POLT1_SIZE_PACKED, t1->vec+i);
}
void unpack_pk_param_iib(unsigned char rho[SEEDBYTES],
               polyveck *t1,
               const unsigned char pk[PK_SIZE_PACKED])
{
  unsigned int i;

  for(i = 0; i < SEEDBYTES; ++i)
    rho[i] = pk[i];
  pk += SEEDBYTES;

  for(i = 0; i < PARAM_K; ++i)
    polyt1_unpack_param_iib(t1->vec+i, pk + i*POLT1_SIZE_PACKED);
}

/*************************************************
* pack the secret key sk, 
* where sk = rho|key|hash(pk)|s1|s2|t0
**************************************************/
void pack_sk_param_iib(unsigned char sk[SK_SIZE_PACKED],
             const unsigned char buf[2*SEEDBYTES + CRHBYTES],
             const polyvecl *s1,
             const polyveck *s2,
             const polyveck *t0)
{
  unsigned int i;

  for(i = 0; i < 2*SEEDBYTES + CRHBYTES; ++i)
    sk[i] = buf[i];
  sk += 2*SEEDBYTES + CRHBYTES;

  for(i = 0; i < PARAM_L; ++i)
    polyeta1_pack_param_iib(sk + i*POLETA1_SIZE_PACKED, s1->vec+i);
  sk += PARAM_L*POLETA1_SIZE_PACKED;

  for(i = 0; i < PARAM_K; ++i)
    polyeta2_pack_param_iib(sk + i*POLETA2_SIZE_PACKED, s2->vec+i);
  sk += PARAM_K*POLETA2_SIZE_PACKED;

  for(i = 0; i < PARAM_K; ++i)
    polyt0_pack_param_iib(sk + i*POLT0_SIZE_PACKED, t0->vec+i);
}
void unpack_sk_param_iib(unsigned char buf[2*SEEDBYTES + CRHBYTES],
               polyvecl *s1,
               polyveck *s2,
               polyveck *t0,
               const unsigned char sk[SK_SIZE_PACKED])
{
  unsigned int i;

  for(i = 0; i < 2*SEEDBYTES + CRHBYTES; ++i)
    buf[i] = sk[i];
  sk += 2*SEEDBYTES + CRHBYTES;

  for(i=0; i < PARAM_L; ++i)
    polyeta1_unpack_param_iib(s1->vec+i, sk + i*POLETA1_SIZE_PACKED);
  sk += PARAM_L*POLETA1_SIZE_PACKED;
  
  for(i=0; i < PARAM_K; ++i)
    polyeta2_unpack_param_iib(s2->vec+i, sk + i*POLETA2_SIZE_PACKED);
  sk += PARAM_K*POLETA2_SIZE_PACKED;

  for(i=0; i < PARAM_K; ++i)
    polyt0_unpack_param_iib(t0->vec+i, sk + i*POLT0_SIZE_PACKED);
}

/*************************************************
* pack the signature sm, 
* where sm = z|h|c
**************************************************/
void pack_sig_param_iib(unsigned char sm[SIG_SIZE_PACKED],
              const polyvecl *z,
              const polyveck *h,
              const poly *c)
{
  unsigned int i, j, k;
  uint64_t signs, mask;

  for(i = 0; i < PARAM_L; ++i)
    polyz_pack_param_iib(sm + i*POLZ_SIZE_PACKED, z->vec+i);
  sm += PARAM_L*POLZ_SIZE_PACKED;

  /* Encode h */
  k = 0;
  for(i = 0; i < PARAM_K; ++i) {
    for(j = 0; j < PARAM_N; ++j)
      if(h->vec[i].coeffs[j] == 1)
        sm[k++] = j;

    sm[OMEGA + i] = k;
  }
  while(k < OMEGA) sm[k++] = 0;
  sm += OMEGA + PARAM_K;
  
  /* Encode c */
  signs = 0;
  mask = 1;
  for(i = 0; i < PARAM_N/8; ++i) {
    sm[i] = 0;
    for(j = 0; j < 8; ++j) {
      if(c->coeffs[8*i+j] != 0) {
        sm[i] |= (1 << j);
        if(c->coeffs[8*i+j] == (PARAM_Q - 1)) signs |= mask;
        mask <<= 1;
      }
    }
  }
  sm += PARAM_N/8;
  for(i = 0; i < 8; ++i)
    sm[i] = signs >> 8*i;
}
void unpack_sig_param_iib(polyvecl *z,
                polyveck *h,
                poly *c,
                const unsigned char sm[SIG_SIZE_PACKED])
{
  unsigned int i, j, k;
  uint64_t signs, mask;

  for(i = 0; i < PARAM_L; ++i)
    polyz_unpack_param_iib(z->vec+i, sm + i*POLZ_SIZE_PACKED);
  sm += PARAM_L*POLZ_SIZE_PACKED;

  /* Decode h */
  k = 0;
  for(i = 0; i < PARAM_K; ++i) {
    for(j = 0; j < PARAM_N; ++j)
      h->vec[i].coeffs[j] = 0;

    for(j = k; j < sm[OMEGA + i]; ++j)
      h->vec[i].coeffs[sm[j]] = 1;

    k = sm[OMEGA + i];
  }
  sm += OMEGA + PARAM_K;

  /* Decode c */
  for(i = 0; i < PARAM_N; ++i)
    c->coeffs[i] = 0;

  signs = 0;
  for(i = 0; i < 8; ++i)
    signs |= (uint64_t)sm[PARAM_N/8+i] << 8*i;

  mask = 1;
  for(i = 0; i < PARAM_N/8; ++i) {
    for(j = 0; j < 8; ++j) {
      if((sm[i] >> j) & 0x01) {
        c->coeffs[8*i+j] = (signs & mask) ? PARAM_Q - 1 : 1;
        mask <<= 1;
      }
    }
  }
}
