#include "crypto_rsa.h"

/* Reference: https://doc.ecoscentric.com/ref/openssl-crypto-evp-pkey-keygen.html */
int rsa_new_key(EVP_PKEY *pkey, int bits) {
    int status = 1;
    EVP_PKEY_CTX *ctx;
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        // Error handling
        status = 0;
    }
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        /* Error */
        status = 0;
    }
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits) <= 0) {
        /* Error */
        status = 0;
    }

    /* Generate key */
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        /* Error */
        status = 0;
    }

    return status;
}

int rsa_encrypt(EVP_PKEY *pkey,
                unsigned char *bytes,
                int bytes_len,
                unsigned char *encrypted_key,
                int encrypted_key_len,
                unsigned char *iv,
                unsigned char *cipher_bytes) {
    EVP_CIPHER_CTX *ctx;
    int cipher_bytes_len;
    int len;


    /* Create and initialise the context */
    if (!(ctx = EVP_CIPHER_CTX_new())) {
        /* Handle errors */
    }

    /* Initialise the envelope seal operation. This operation generates
     * a key for the provided cipher, and then encrypts that key a number
     * of times (one for each public key provided in the pub_key array). In
     * this example the array size is just one. This operation also
     * generates an IV and places it in iv. */
    if (1 != EVP_SealInit(ctx, EVP_aes_256_cbc(), &encrypted_key,
                          &encrypted_key_len, iv, &pkey, 1)) {
        /* Handle errors */
    }

    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_SealUpdate can be called multiple times if necessary
     */
    if (1 != EVP_SealUpdate(ctx, cipher_bytes, &len, bytes, bytes_len)) {
        /* Handle errors */
    }
    cipher_bytes_len = len;

    /* Finalise the encryption. Further cipher_bytes bytes may be written at
     * this stage.
     */
    if (1 != EVP_SealFinal(ctx, cipher_bytes + len, &len)) {
        /* Handle errors */
    }
    cipher_bytes_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return cipher_bytes_len;
}
