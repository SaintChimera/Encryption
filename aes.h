typedef enum {
	AES_CYPHER_128,
	AES_CYPHER_192,
	AES_CYPHER_256,
} AES_CYPHER_T;

#ifdef __GNUC__ >= 3
	#include <cstdint>
#endif

int aes_encrypt_ecb(AES_CYPHER_T mode, uint8_t *data, int len, uint8_t *key);
int aes_decrypt_ecb(AES_CYPHER_T mode, uint8_t *data, int len, uint8_t *key);
int aes_encrypt_cbc(AES_CYPHER_T mode, uint8_t *data, int len, uint8_t *key, uint8_t *iv);
int aes_decrypt_cbc(AES_CYPHER_T mode, uint8_t *data, int len, uint8_t *key, uint8_t *iv);
