#include <stdlib.h>
#include <oqs/sig.h>
#include <oqs/sig_aigis-sig.h>

#if defined OQS_ENABLE_SIG_aigis_sig_param_iib

OQS_SIG* OQS_SIG_aigis_sig_param_iib_new() {
    OQS_SIG* sig = malloc(sizeof(OQS_SIG));
    if (sig == NULL) {
        return NULL;
    }
    sig->method_name = OQS_SIG_alg_aigis_sig_param_iib;
    sig->alg_version = "";

    // Dummy parameters for CACR algorithms
    sig->claimed_nist_level = 1;
    sig->euf_cma = true;

    sig->length_public_key = OQS_SIG_aigis_sig_param_iib_length_public_key;
    sig->length_secret_key = OQS_SIG_aigis_sig_param_iib_length_secret_key;
    sig->length_signature = OQS_SIG_aigis_sig_param_iib_length_signature;

    sig->keypair = OQS_SIG_aigis_sig_param_iib_keypair;
    sig->sign = OQS_SIG_aigis_sig_param_iib_sign;
    sig->verify = OQS_SIG_aigis_sig_param_iib_verify;

    return sig;
}

extern int msig_keygen_param_iib(uint8_t* pk, uint8_t* sk);
extern int msig_sign_param_iib(uint8_t* sk, uint8_t* m, size_t mlen, uint8_t* sm, size_t* smlen);
extern int msig_verf_param_iib(uint8_t* pk, uint8_t* sm, size_t smlen, uint8_t* m, size_t mlen);

OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iib_keypair(uint8_t* public_key, uint8_t* secret_key) {
    return (OQS_STATUS)msig_keygen_param_iib(public_key, secret_key);
}
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iib_sign(uint8_t* signature, size_t* signature_len,  uint8_t* message, size_t message_len,  uint8_t* secret_key) {
    return (OQS_STATUS)msig_sign_param_iib(secret_key, message, message_len, signature, signature_len);
}
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iib_verify( uint8_t* message, size_t message_len,  uint8_t* signature, size_t signature_len,  uint8_t* public_key) {
    return (OQS_STATUS)msig_verf_param_iib(public_key, signature, signature_len, message, message_len);
}
#endif