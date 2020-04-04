void *RC4_init(char *key, int key_size);
int RC4_dest(void *context);
int RC4_crypt(void *context, unsigned char *textbuffer, int textbuffer_size);
