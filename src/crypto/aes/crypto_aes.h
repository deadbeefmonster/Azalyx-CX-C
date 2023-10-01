/*
 * References:
 * https://www.openssl.org/docs/manmaster/man3/RAND_bytes.html (random bytes)
 * https://wiki.openssl.org/index.php/EVP_Symmetric_Encryption_and_Decryption (copy/paste pretty much)
 * https://github.com/saju/misc/blob/master/misc/openssl_aes.c (another example of using EVP for AES)
 */

#ifndef AZALYXCX_CRYPTO_AES_CRYPTO_AES_H
#define AZALYXCX_CRYPTO_AES_CRYPTO_AES_H

#include <glib.h>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

struct aes_key {
	unsigned char key[32];	/* 32 bytes (256 bits) */
	unsigned char iv[16];	/* 16 bytes (128 bits) */
};

int aes_encrypt(unsigned char *plaintext, int plaintext_len, struct aes_key *aes_key, unsigned char *ciphertext);

int aes_decrypt(unsigned char *ciphertext, int ciphertext_len, struct aes_key *aes_key, unsigned char *plaintext);

void aes_generate_new_key_iv(struct aes_key *aes_key);

#endif				/* AZALYXCX_CRYPTO_AES_CRYPTO_AES_H */
