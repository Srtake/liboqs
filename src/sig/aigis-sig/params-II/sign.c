#include <stdint.h>
#include<stdio.h>
#include "api.h"
#include "params.h"
#include "sign.h"
#include "fips202.h"
#include "fips202x4.h"
#include "poly.h"
#include "polyvec.h"
#include "packing.h"
#include "randombytes.h"
#include "aes256ctr.h"


#ifdef USE_AES
void expand_mat_param_ii(polyvecl mat[PARAM_K], const unsigned char rho[SEEDBYTES]) {
	unsigned int i, j;
#if PARAM_L == 3 && PARAM_K == 4
	unsigned int nblocks = 7;
	unsigned char buf[896];
#elif PARAM_L == 4 && PARAM_K == 5
	unsigned int nblocks = 8;
	unsigned char buf[1024];
#elif PARAM_L == 5 && PARAM_K == 6
	unsigned int nblocks = 9;
	unsigned char buf[1152];
#endif
	aes256ctr_ctx state;

	for (i = 0; i < PARAM_K; ++i)
		for (j = 0; j < PARAM_L; ++j)
		{
			aes256ctr_init(&state, rho, (i << 8) + j);
			aes256ctr_squeezeblocks(buf, nblocks, &state);
			poly_uniform_param_ii(&mat[i].vec[j], buf);
		}
}
#elif PARAM_L == 3 && PARAM_K == 4
void expand_mat_param_ii(polyvecl mat[4], const unsigned char rho[SEEDBYTES])
{
  unsigned int i;
  unsigned char inbuf[4][SEEDBYTES + 1];
  unsigned char outbuf[4][6*SHAKE128_RATE];

  for(i = 0; i < SEEDBYTES; ++i) {
    inbuf[0][i] = rho[i];
    inbuf[1][i] = rho[i];
    inbuf[2][i] = rho[i];
    inbuf[3][i] = rho[i];
  }

  for(i = 0; i < 3; ++i) {
    inbuf[0][SEEDBYTES] = 0 + (i << 4);
    inbuf[1][SEEDBYTES] = 1 + (i << 4);
    inbuf[2][SEEDBYTES] = 2 + (i << 4);
    inbuf[3][SEEDBYTES] = 3 + (i << 4);

    shake128_4x(outbuf[0], outbuf[1], outbuf[2], outbuf[3], 6*SHAKE128_RATE,
                inbuf[0], inbuf[1], inbuf[2], inbuf[3], SEEDBYTES + 1);

    poly_uniform_param_ii(&mat[0].vec[i], outbuf[0]);
    poly_uniform_param_ii(&mat[1].vec[i], outbuf[1]);
    poly_uniform_param_ii(&mat[2].vec[i], outbuf[2]);
    poly_uniform_param_ii(&mat[3].vec[i], outbuf[3]);
  }
}

#elif PARAM_L == 4 && PARAM_K == 5

void expand_mat_param_ii(polyvecl *mat, const unsigned char rho[SEEDBYTES])
{
  unsigned int i;
  unsigned char inbuf[4][SEEDBYTES + 1];
  unsigned char outbuf[4][7*SHAKE128_RATE];

  for(i = 0; i < SEEDBYTES; ++i) {
    inbuf[0][i] = rho[i];
    inbuf[1][i] = rho[i];
    inbuf[2][i] = rho[i];
    inbuf[3][i] = rho[i];
  }

  for(i = 0; i < 5; ++i) {
    inbuf[0][SEEDBYTES] = i + (0 << 4);
    inbuf[1][SEEDBYTES] = i + (1 << 4);
    inbuf[2][SEEDBYTES] = i + (2 << 4);
    inbuf[3][SEEDBYTES] = i + (3 << 4);

    shake128_4x(outbuf[0], outbuf[1], outbuf[2], outbuf[3], 7*SHAKE128_RATE, inbuf[0], inbuf[1], inbuf[2], inbuf[3], SEEDBYTES + 1);

    poly_uniform_param_ii(&mat[i].vec[0], outbuf[0]);
    poly_uniform_param_ii(&mat[i].vec[1], outbuf[1]);
    poly_uniform_param_ii(&mat[i].vec[2], outbuf[2]);
    poly_uniform_param_ii(&mat[i].vec[3], outbuf[3]);
  }
}
#elif PARAM_L == 5 && PARAM_K == 6

void expand_mat_param_ii(polyvecl mat[6], const unsigned char rho[SEEDBYTES])
{
	unsigned int i;
	unsigned char inbuf[4][SEEDBYTES + 1];
	unsigned char outbuf[4][8 * SHAKE128_RATE];

	for (i = 0; i < SEEDBYTES; ++i) {
		inbuf[0][i] = rho[i];
		inbuf[1][i] = rho[i];
		inbuf[2][i] = rho[i];
		inbuf[3][i] = rho[i];
	}

	for (i = 0; i < 4; i += 2) {
		inbuf[0][SEEDBYTES] = 0 + (i << 4);
		inbuf[1][SEEDBYTES] = 1 + (i << 4);
		inbuf[2][SEEDBYTES] = 2 + (i << 4);
		inbuf[3][SEEDBYTES] = 3 + (i << 4);

		shake128_4x(outbuf[0], outbuf[1], outbuf[2], outbuf[3], 8 * SHAKE128_RATE,
			inbuf[0], inbuf[1], inbuf[2], inbuf[3], SEEDBYTES + 1);

		poly_uniform_param_ii(&mat[0].vec[i], outbuf[0]);
		poly_uniform_param_ii(&mat[1].vec[i], outbuf[1]);
		poly_uniform_param_ii(&mat[2].vec[i], outbuf[2]);
		poly_uniform_param_ii(&mat[3].vec[i], outbuf[3]);

		inbuf[0][SEEDBYTES] = 4 + (i << 4);
		inbuf[1][SEEDBYTES] = 5 + (i << 4);
		inbuf[2][SEEDBYTES] = 0 + ((i + 1) << 4);
		inbuf[3][SEEDBYTES] = 1 + ((i + 1) << 4);

		shake128_4x(outbuf[0], outbuf[1], outbuf[2], outbuf[3], 8 * SHAKE128_RATE,
			inbuf[0], inbuf[1], inbuf[2], inbuf[3], SEEDBYTES + 1);

		poly_uniform_param_ii(&mat[4].vec[i], outbuf[0]);
		poly_uniform_param_ii(&mat[5].vec[i], outbuf[1]);
		poly_uniform_param_ii(&mat[0].vec[i + 1], outbuf[2]);
		poly_uniform_param_ii(&mat[1].vec[i + 1], outbuf[3]);

		inbuf[0][SEEDBYTES] = 2 + ((i + 1) << 4);
		inbuf[1][SEEDBYTES] = 3 + ((i + 1) << 4);
		inbuf[2][SEEDBYTES] = 4 + ((i + 1) << 4);
		inbuf[3][SEEDBYTES] = 5 + ((i + 1) << 4);

		shake128_4x(outbuf[0], outbuf[1], outbuf[2], outbuf[3], 8 * SHAKE128_RATE,
			inbuf[0], inbuf[1], inbuf[2], inbuf[3], SEEDBYTES + 1);

		poly_uniform_param_ii(&mat[2].vec[i + 1], outbuf[0]);
		poly_uniform_param_ii(&mat[3].vec[i + 1], outbuf[1]);
		poly_uniform_param_ii(&mat[4].vec[i + 1], outbuf[2]);
		poly_uniform_param_ii(&mat[5].vec[i + 1], outbuf[3]);
	}

	inbuf[0][SEEDBYTES] = 0 + (4 << 4);
	inbuf[1][SEEDBYTES] = 1 + (4 << 4);
	inbuf[2][SEEDBYTES] = 2 + (4 << 4);
	inbuf[3][SEEDBYTES] = 3 + (4 << 4);

	shake128_4x(outbuf[0], outbuf[1], outbuf[2], outbuf[3], 8 * SHAKE128_RATE,
		inbuf[0], inbuf[1], inbuf[2], inbuf[3], SEEDBYTES + 1);

	poly_uniform_param_ii(&mat[0].vec[4], outbuf[0]);
	poly_uniform_param_ii(&mat[1].vec[4], outbuf[1]);
	poly_uniform_param_ii(&mat[2].vec[4], outbuf[2]);
	poly_uniform_param_ii(&mat[3].vec[4], outbuf[3]);

	inbuf[0][SEEDBYTES] = 4 + (4 << 4);
	inbuf[1][SEEDBYTES] = 5 + (4 << 4);

	shake128_4x(outbuf[0], outbuf[1], outbuf[2], outbuf[3], 8 * SHAKE128_RATE,
		inbuf[0], inbuf[1], inbuf[2], inbuf[3], SEEDBYTES + 1);

	poly_uniform_param_ii(&mat[4].vec[4], outbuf[0]);
	poly_uniform_param_ii(&mat[5].vec[4], outbuf[1]);
}
#endif

void challenge_param_ii(poly *c,
               const unsigned char mu[CRHBYTES],
               const polyveck *w1) 
{
  unsigned int i, b, pos;
  unsigned char inbuf[CRHBYTES + PARAM_K*POLW1_SIZE_PACKED];
  unsigned char outbuf[SHAKE256_RATE];
  uint64_t state[25], signs, mask;

  for(i = 0; i < CRHBYTES; ++i)
    inbuf[i] = mu[i];
  for(i = 0; i < PARAM_K; ++i)
    polyw1_pack_param_ii(inbuf + CRHBYTES + i*POLW1_SIZE_PACKED, w1->vec+i);

  shake256_absorb(state, inbuf, sizeof(inbuf));
  shake256_squeezeblocks(outbuf, 1, state);

  signs = 0;
  for(i = 0; i < 8; ++i)
    signs |= (uint64_t)outbuf[i] << 8*i;

  pos = 8;
  mask = 1;

  for(i = 0; i < PARAM_N; ++i)
    c->coeffs[i] = 0;

  for(i = 196; i < 256; ++i) {
    do {
      if(pos >= SHAKE256_RATE) {
        shake256_squeezeblocks(outbuf, 1, state);
        pos = 0;
      }

      b = outbuf[pos++];
    } while(b > i);

    c->coeffs[i] = c->coeffs[b];
    c->coeffs[b] = (signs & mask) ? PARAM_Q - 1 : 1;
    mask <<= 1;
  }
}

/*************************************************
* generate a pair of public key pk and secret key sk, 
* where pk = rho|t1
*       sk = rho|key|hash(pk)|s1|s2|t0
**************************************************/
int msig_keygen_param_ii(unsigned char *pk, unsigned char *sk)
{
  unsigned int i;
  unsigned char buf[3*SEEDBYTES + CRHBYTES]; //buf = r|rho|key|hash(pk)
  uint16_t nonce = 0;
  polyvecl mat[PARAM_K];
  polyvecl s1, s1hat;
  polyveck s2, t, t1, t0;
  
  randombytes(buf, SEEDBYTES);
  shake256(buf, 3*SEEDBYTES, buf, SEEDBYTES); 
  

  expand_mat_param_ii(mat, &buf[SEEDBYTES]);

#ifdef USE_AES
  for (i = 0; i < PARAM_L; ++i)
	  poly_uniform_eta1_param_ii(&s1.vec[i], buf, nonce++);
#elif PARAM_L==3
  poly_uniform_eta1_3x_param_ii(&s1.vec[0],&s1.vec[1],&s1.vec[2],buf, nonce,nonce+1,nonce+2);
  nonce += 3;
#elif PARAM_L==4
  poly_uniform_eta1_4x_param_ii(&s1.vec[0],
                         &s1.vec[1],
                         &s1.vec[2],
                         &s1.vec[3],buf,nonce,nonce+1,nonce+2,nonce+3);
  nonce += 4;
#elif PARAM_L==5
  poly_uniform_eta1_4x_param_ii(&s1.vec[0],
	  &s1.vec[1],
	  &s1.vec[2],
	  &s1.vec[3],buf,nonce,nonce+1,nonce+2,nonce+3);
  nonce += 4;
  poly_uniform_eta1_param_ii(&s1.vec[4], buf, nonce++);
#endif
    
#ifdef USE_AES
  for (i = 0; i < PARAM_K; ++i)
	  poly_uniform_eta2_param_ii(&s2.vec[i], buf, nonce++);
#elif PARAM_K == 4
  poly_uniform_eta2_4x_param_ii(&s2.vec[0],
                         &s2.vec[1],
                         &s2.vec[2],
                         &s2.vec[3],buf,nonce,nonce+1,nonce+2,nonce+3);
#elif PARAM_K == 5
  poly_uniform_eta2_4x_param_ii(&s2.vec[0],
                         &s2.vec[1],
                         &s2.vec[2],
                         &s2.vec[3],buf,nonce,nonce+1,nonce+2,nonce+3);
  poly_uniform_eta2_param_ii(&s2.vec[4], buf, nonce+4);
#elif PARAM_K == 6
  poly_uniform_eta2_4x_param_ii(&s2.vec[0],
	  &s2.vec[1],
	  &s2.vec[2],
	  &s2.vec[3], buf, nonce, nonce + 1, nonce + 2, nonce + 3);
  poly_uniform_eta2_param_ii(&s2.vec[4], buf, nonce + 4);
  poly_uniform_eta2_param_ii(&s2.vec[5], buf, nonce + 5);
#endif

  s1hat = s1;
  polyvecl_ntt_param_ii(&s1hat);
  for(i = 0; i < PARAM_K; ++i) {

    polyvecl_pointwise_acc_invmontgomery_param_ii(&t.vec[i], mat+i, &s1hat);//output coefficient  <=2*Q
    poly_invntt_montgomery_param_ii(t.vec+i);//output coefficient  <=2*Q
  }


  polyveck_add_param_ii(&t, &t, &s2);//output coefficient <=4*Q
  polyveck_freeze4q_param_ii(&t);
  polyveck_power2round_param_ii(&t1, &t0, &t);
  pack_pk_param_ii(pk, &buf[SEEDBYTES], &t1);
  

  shake256(&buf[3*SEEDBYTES], CRHBYTES, pk, SIG_PUBLICKEYBYTES);
  pack_sk_param_ii(sk,&buf[SEEDBYTES], &s1, &s2, &t0);

  return 0;

}

/*************************************************
* create a signature sm on message m, where 
* sm = z|h|c
**************************************************/
int msig_sign_param_ii(unsigned char *sk,
	unsigned char *m, unsigned long long mlen,
	unsigned char *sm, unsigned long long *smlen)
{
	unsigned long long i;
	unsigned int n;
	unsigned char *buf;
	uint16_t nonce = 0;
	poly     c, chat;
	polyvecl mat[PARAM_K], s1, y, yhat, z;
	polyveck s2, t0, w, w1;
	polyveck h, wcs2, ct0, tmp;

	buf = (unsigned char *)malloc(2 * SEEDBYTES + CRHBYTES + mlen);
	if (buf == NULL)
		return -1;
	unpack_sk_param_ii(buf, &s1, &s2, &t0, sk);

	for (i = 0; i<mlen; i++)
		buf[2 * SEEDBYTES + CRHBYTES + i] = m[i];
	shake256(&buf[2 * SEEDBYTES], CRHBYTES, &buf[2 * SEEDBYTES], CRHBYTES + mlen);

	expand_mat_param_ii(mat, buf);
	polyvecl_ntt_param_ii(&s1);
	polyveck_ntt_param_ii(&s2);
	polyveck_ntt_param_ii(&t0);

#ifdef USE_AES
	shake256(&buf[SEEDBYTES], SEEDBYTES, &buf[SEEDBYTES], SEEDBYTES + CRHBYTES);
#endif

rej:
#ifdef USE_AES
	for (i = 0; i < PARAM_L; ++i)
		poly_uniform_gamma1m1_param_ii(&y.vec[i], &buf[SEEDBYTES], nonce++);
#elif PARAM_L == 3
	poly_uniform_gamma1m1_3x_param_ii(&y.vec[0], &y.vec[1], &y.vec[2], &buf[SEEDBYTES],
		nonce, nonce + 1, nonce + 2);
	nonce += 3;
#elif PARAM_L == 4
	poly_uniform_gamma1m1_4x_param_ii(&y.vec[0], &y.vec[1], &y.vec[2], &y.vec[3], &buf[SEEDBYTES],
		nonce, nonce + 1, nonce + 2, nonce + 3);
	nonce += 4;
#elif PARAM_L == 5
	poly_uniform_gamma1m1_4x_param_ii(&y.vec[0], &y.vec[1], &y.vec[2], &y.vec[3], &buf[SEEDBYTES],
		nonce, nonce + 1, nonce + 2, nonce + 3);
	poly_uniform_gamma1m1_param_ii(&y.vec[4], &buf[SEEDBYTES], nonce+4);
	nonce += 5;
#endif 

	yhat = y;
	polyvecl_ntt_param_ii(&yhat);
	for (i = 0; i < PARAM_K; ++i) {
		polyvecl_pointwise_acc_invmontgomery_param_ii(w.vec + i, mat + i, &yhat);//output coefficient  <=2*Q
		poly_invntt_montgomery_param_ii(w.vec + i);//output coefficient  <= 2*Q
	}

	polyveck_freeze2q_param_ii(&w);
	polyveck_decompose_param_ii(&w1, &tmp, &w);
	challenge_param_ii(&c, &buf[2 * SEEDBYTES], &w1);

	chat = c;
	poly_ntt_param_ii(&chat);

	

	//check z
	for (i = 0; i < PARAM_L; ++i) {
		poly_pointwise_invmontgomery_param_ii(z.vec + i, &chat, s1.vec + i);//output coefficient  <=2*Q
		poly_invntt_montgomery_param_ii(z.vec + i);//output coefficient  <=2*Q
	}
	polyvecl_add_param_ii(&z, &z, &y);//output coefficient  <=4*Q
	polyvecl_freeze4q_param_ii(&z);
	if (polyvecl_chknorm_param_ii(&z, GAMMA1 - BETA1))
		goto rej;

	//check r0 and r1=w1?
	for (i = 0; i < PARAM_K; ++i) {
		poly_pointwise_invmontgomery_param_ii(wcs2.vec + i, &chat, s2.vec + i);//output coefficient  <=2*Q
		poly_invntt_montgomery_param_ii(wcs2.vec + i);//output coefficient  <=2*Q
	}
	polyveck_sub_param_ii(&tmp, &tmp, &wcs2);//output coefficient  <=4*Q
	polyveck_freeze4q_param_ii(&tmp);
	if (polyveck_chknorm_param_ii(&tmp, GAMMA2 - BETA2))
		goto rej;

	//check ct0
	for (i = 0; i < PARAM_K; ++i) {
		poly_pointwise_invmontgomery_param_ii(ct0.vec + i, &chat, t0.vec + i);//output coefficient  <=2*Q
		poly_invntt_montgomery_param_ii(ct0.vec + i);//output coefficient  <=2*Q
	}
	polyveck_freeze2q_param_ii(&ct0);
	if (polyveck_chknorm_param_ii(&ct0, GAMMA2))
		goto rej;

	//check hw(h)
	polyveck_add_param_ii(&tmp, &tmp, &ct0);//output coefficient  <=2*Q
	polyveck_freeze2q_param_ii(&tmp);
	n = polyveck_make_hint_param_ii(&h, &tmp, &w1);
	if (n > OMEGA)
		goto rej;

	pack_sig_param_ii(sm, &z, &h, &c);

	*smlen = SIG_BYTES;

	free(buf);
	return 0;
}

int msig_verf_param_ii(unsigned char *pk,
	unsigned char *sm, unsigned long long smlen,
	unsigned char *m, unsigned long long mlen)
{
	unsigned long long i;
	unsigned char rho[SEEDBYTES];
	unsigned char *buf;
	poly     c, chat, cp;
	polyvecl mat[PARAM_K], z;
	polyveck t1, w1, h, tmp1, tmp2;

	if (smlen < SIG_BYTES)
		return -1;

	unpack_pk_param_ii(rho, &t1, pk);
	unpack_sig_param_ii(&z, &h, &c, sm);
	if (polyvecl_chknorm_param_ii(&z, GAMMA1 - BETA1))
		return -1;

	buf = (unsigned char*)malloc(CRHBYTES + mlen);
	if (buf == NULL)
		return -1;
	for (i = 0; i<mlen; i++)
		buf[CRHBYTES + i] = m[i];

	shake256(buf, CRHBYTES, pk, SIG_PUBLICKEYBYTES);
	shake256(buf, CRHBYTES, buf, CRHBYTES + mlen);

	expand_mat_param_ii(mat, rho);

	polyvecl_ntt_param_ii(&z);
	for (i = 0; i < PARAM_K; ++i)
		polyvecl_pointwise_acc_invmontgomery_param_ii(tmp1.vec + i, mat + i, &z);//output coefficient  <=2*Q

	chat = c;
	poly_ntt_param_ii(&chat);
	polyveck_shiftl_param_ii(&t1, PARAM_D);
	polyveck_ntt_param_ii(&t1);
	for (i = 0; i < PARAM_K; ++i)
		poly_pointwise_invmontgomery_param_ii(tmp2.vec + i, &chat, t1.vec + i);//output coefficient  <=2*Q

	polyveck_sub_param_ii(&tmp1, &tmp1, &tmp2);//output coefficient  <=4*Q
	polyveck_invntt_montgomery_param_ii(&tmp1);//output coefficient  <= 2*Q

	polyveck_freeze2q_param_ii(&tmp1);
	polyveck_use_hint_param_ii(&w1, &tmp1, &h);

	challenge_param_ii(&cp, buf, &w1);
	for (i = 0; i < PARAM_N; ++i)
		if (c.coeffs[i] != cp.coeffs[i])
			return -1;

	free(buf);
	return 0;
}