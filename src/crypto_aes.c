#include "crypto_aes.h"

void aes_generate_new_key_iv(struct aes_key *aes_key) {
    // Generate AES key bytes
    if (1 != RAND_priv_bytes(aes_key->key, 32)) {
        g_error("1 != RAND_priv_bytes(aes_key->key, 32)");
    }

    // Generate AES iv bytes
    if (1 != RAND_priv_bytes(aes_key->iv, 16)) {
        g_error("1 != RAND_priv_bytes(aes_key->iv, 16)");
    }
}

int aes_encrypt(unsigned char *plaintext, int plaintext_len, struct aes_key *aes_key, unsigned char *ciphertext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        g_error("!(ctx = EVP_CIPHER_CTX_new())");
    }

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key->key, aes_key->iv)) {
        g_error("1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key->key, aes_key->iv)");
    }


    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)) {
        g_error("1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len)");
    }
    ciphertext_len = len;


    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)) {
        g_error("1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len)");
    }
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int aes_decrypt(unsigned char *ciphertext, int ciphertext_len, struct aes_key *aes_key, unsigned char *plaintext) {
    EVP_CIPHER_CTX *ctx;

    int len;

    int plaintext_len;

    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        g_error("!(ctx = EVP_CIPHER_CTX_new())");
    }

    /*
     * Initialise the decryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if (1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key->key, aes_key->iv)) {
        g_error("1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, aes_key->key, aes_key->iv)");
    }

    /*
     * Provide the message to be decrypted, and obtain the plaintext output.
     * EVP_DecryptUpdate can be called multiple times if necessary.
     */
    if (1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)) {
        g_error("1 != EVP_DecryptUpdate(ctx, plaintext, &len, ciphertext, ciphertext_len)");
    }
    plaintext_len = len;

    /*
     * Finalise the decryption. Further plaintext bytes may be written at
     * this stage.
     */
    if (1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)) {
        g_error("1 != EVP_DecryptFinal_ex(ctx, plaintext + len, &len)");
    }
    plaintext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return plaintext_len;
}