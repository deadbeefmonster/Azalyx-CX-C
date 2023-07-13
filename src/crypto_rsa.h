/* References:
 * - https://wiki.openssl.org/index.php/EVP_Asymmetric_Encryption_and_Decryption_of_an_Envelope
 * - "Network Security with OpenSSL Cryptography for Secure Communications" book from O'Reilly Media
 */
#ifndef AZALYXCX__CRYPTO_RSA_H_
#define AZALYXCX__CRYPTO_RSA_H_

#include <glib.h>
#include <openssl/evp.h>
#include <openssl/rsa.h>
#include <openssl/rand.h>

//int rsa_encrypt();
//int rsa_decrypt();
int rsa_encrypt(EVP_PKEY *pkey,
                unsigned char *bytes,
                int bytes_len,
                unsigned char *encrypted_key,
                int encrypted_key_len,
                unsigned char *iv,
                unsigned char *cipher_bytes);

/* 2048 bit key */
void rsa_new_key(EVP_PKEY *pkey, int bits);

#endif //AZALYXCX__CRYPTO_RSA_H_
