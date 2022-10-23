unsigned char* plaintext, * plaintext2, * ciphertext;
int plaintext_len, ciphertext_len, plaintext2_len;
struct aes_key* aes_key;

aes_key = g_slice_new(struct aes_key);
ciphertext = g_slice_alloc0(plaintext_len*2);

plaintext = (unsigned char*)"Hello, this is just a test!";
plaintext_len = strlen((const char*)plaintext)+1;
plaintext2 = malloc(plaintext_len);

g_debug("creating random key and iv");
if (1!=aes_generate_new_key_iv(aes_key)) {
g_error("aes_generate_new_key_iv() failed!");
}
g_debug("done creating random key and iv");
g_debug("calling bytes_to_hex");
GString* aes_key_key_bytes = bytes_to_hex(aes_key->key, 32);
g_debug("aes_key->key=%s", aes_key_key_bytes->str);
g_debug("calling bytes_to_hex");
GString* aes_key_iv_bytes = bytes_to_hex(aes_key->iv, 16);
g_debug("aes_key->iv=%s", aes_key_iv_bytes->str);


//  g_debug(aes_key->iv);
g_debug("encrypting plaintext: %s", plaintext);
ciphertext_len = aes_encrypt(plaintext, plaintext_len, aes_key, ciphertext);
g_debug("ciphertext_len=%i", ciphertext_len);

g_debug("calling bytes_to_hex");
GString* ciphertext_bytes = bytes_to_hex(ciphertext, ciphertext_len);
g_debug("ciphertext_bytes=%s", ciphertext_bytes->str);

g_debug("decrypting ciphertext now");
//int aes_decrypt(unsigned char *ciphertext, int ciphertext_len, struct aes_key *aes_key, unsigned char *plaintext) {
plaintext2_len = aes_decrypt(ciphertext, ciphertext_len, aes_key, plaintext2);
g_debug("plaintext2=%s", plaintext2);
g_slice_free1(plaintext_len*2, ciphertext);
free(plaintext2);
g_slice_free(struct aes_key, aes_key);