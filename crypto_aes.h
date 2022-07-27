/*
 * References:
 * https://www.openssl.org/docs/manmaster/man3/RAND_bytes.html (random bytes)
 * https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption (copy/paste pretty much)
 * https://github.com/saju/misc/blob/master/misc/openssl_aes.c (another example of using EVP for AES)
 */

#ifndef CLUTCHINGPEARLS_CRYPTO_AES_H
#define CLUTCHINGPEARLS_CRYPTO_AES_H

#include <glib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

int aes_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
				unsigned char *iv, unsigned char *ciphertext);
int aes_decrypt(unsigned char *ciphertext,
				int ciphertext_len,
				unsigned char *key,
				unsigned char *iv,
				unsigned char *plaintext);

int aes_generate_256key_and_iv(unsigned char *key, unsigned char *iv);

#endif //CLUTCHINGPEARLS_CRYPTO_AES_H
