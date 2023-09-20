#include "crypto/rsa/crypto_rsa.h"

/* Reference: https://doc.ecoscentric.com/ref/openssl-crypto-evp-pkey-keygen.html */
void rsa_new_key(EVP_PKEY *pkey, int bits) {
    gboolean status = TRUE;
    EVP_PKEY_CTX *ctx;
    ctx = EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL);
    if (!ctx) {
        fprintf(stderr, "FATAL ERROR: EVP_PKEY_CTX_new_id(EVP_PKEY_RSA, NULL): ctx is not OK\n");
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        fprintf(stderr, "FATAL ERROR: EVP_PKEY_keygen_init(ctx) <= 0\n");
        exit(EXIT_FAILURE);
    }
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits) <= 0) {
        fprintf(stderr, "FATAL ERROR: EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits) <= 0\n");
        exit(EXIT_FAILURE);
    }

    /* Generate key */
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        /* Error */
        fprintf(stderr, "FATAL ERROR: EVP_PKEY_keygen(ctx, &pkey) <= 0\n");
        exit(EXIT_FAILURE);
    }
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
        fprintf(stderr, "FATAL ERROR: !(ctx = EVP_CIPHER_CTX_new())\n");
        exit(EXIT_FAILURE);
    }

    /* Initialise the envelope seal operation. This operation generates
     * a key for the provided cipher, and then encrypts that key a number
     * of times (one for each public key provided in the pub_key array). In
     * this example the array size is just one. This operation also
     * generates an IV and places it in iv. */
    if (1 != EVP_SealInit(ctx, EVP_aes_256_cbc(), &encrypted_key,
                          &encrypted_key_len, iv, &pkey, 1)) {
        fprintf(stderr, "FATAL ERROR: 1 != EVP_SealInit(ctx, EVP_aes_256_cbc(), &encrypted_key, &encrypted_key_len, iv, &pkey, 1)\n");
        exit(EXIT_FAILURE);
    }

    /* Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_SealUpdate can be called multiple times if necessary
     */
    if (1 != EVP_SealUpdate(ctx, cipher_bytes, &len, bytes, bytes_len)) {
        fprintf(stderr, "FATAL ERROR: 1 != EVP_SealUpdate(ctx, cipher_bytes, &len, bytes, bytes_len)\n");
        exit(EXIT_FAILURE);
    }
    cipher_bytes_len = len;

    /* Finalise the encryption. Further cipher_bytes bytes may be written at
     * this stage.
     */
    if (1 != EVP_SealFinal(ctx, cipher_bytes + len, &len)) {
        fprintf(stderr, "FATAL ERROR: 1 != EVP_SealFinal(ctx, cipher_bytes + len, &len)\n");
        exit(EXIT_FAILURE);
    }
    cipher_bytes_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return cipher_bytes_len;
}
