#ifndef OQS_SIG_AIGIS_SIG_H
#define OQS_SIG_AIGIS_SIG_H

#include <oqs/oqs.h>

// Aigis-sig PARAM I
#ifdef OQS_ENABLE_SIG_aigis_sig_param_i
#define OQS_SIG_aigis_sig_param_i_length_public_key 1056
#define OQS_SIG_aigis_sig_param_i_length_secret_key 2448
#define OQS_SIG_aigis_sig_param_i_length_signature 1852

OQS_SIG* OQS_SIG_aigis_sig_param_i_new(void);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_i_keypair(uint8_t* public_key, uint8_t* secret_key);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_i_sign(uint8_t* signature, size_t* signature_len, const uint8_t* message, size_t message_len, const uint8_t* secret_key);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_i_verify(const uint8_t* message, size_t message_len, const uint8_t* signature, size_t signature_len, const uint8_t* public_key);
#endif

// Aigis-sig PARAM II
#ifdef OQS_ENABLE_SIG_aigis_sig_param_ii
#define OQS_SIG_aigis_sig_param_ii_length_public_key 1312
#define OQS_SIG_aigis_sig_param_ii_length_secret_key 3376
#define OQS_SIG_aigis_sig_param_ii_length_signature 2445

OQS_SIG* OQS_SIG_aigis_sig_param_ii_new(void);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_ii_keypair(uint8_t* public_key, uint8_t* secret_key);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_ii_sign(uint8_t* signature, size_t* signature_len, const uint8_t* message, size_t message_len, const uint8_t* secret_key);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_ii_verify(const uint8_t* message, size_t message_len, const uint8_t* signature, size_t signature_len, const uint8_t* public_key);
#endif

// Aigis-sig PARAM IIb
#ifdef OQS_ENABLE_SIG_aigis_sig_param_iib
#define OQS_SIG_aigis_sig_param_iib_length_public_key 1312
#define OQS_SIG_aigis_sig_param_iib_length_secret_key 3376
#define OQS_SIG_aigis_sig_param_iib_length_signature 2445

OQS_SIG* OQS_SIG_aigis_sig_param_iib_new(void);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iib_keypair(uint8_t* public_key, uint8_t* secret_key);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iib_sign(uint8_t* signature, size_t* signature_len, const uint8_t* message, size_t message_len, const uint8_t* secret_key);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iib_verify(const uint8_t* message, size_t message_len, const uint8_t* signature, size_t signature_len, const uint8_t* public_key);
#endif

// Aigis-sig PARAM III
#ifdef OQS_ENABLE_SIG_aigis_sig_param_iii
#define OQS_SIG_aigis_sig_param_iii_length_public_key 1568
#define OQS_SIG_aigis_sig_param_iii_length_secret_key 3888
#define OQS_SIG_aigis_sig_param_iii_length_signature 3046


OQS_SIG* OQS_SIG_aigis_sig_param_iii_new(void);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iii_keypair(uint8_t* public_key, uint8_t* secret_key);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iii_sign(uint8_t* signature, size_t* signature_len, const uint8_t* message, size_t message_len, const uint8_t* secret_key);
OQS_API OQS_STATUS OQS_SIG_aigis_sig_param_iii_verify(const uint8_t* message, size_t message_len, const uint8_t* signature, size_t signature_len, const uint8_t* public_key);
#endif

#endif