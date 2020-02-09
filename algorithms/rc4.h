unsigned char *RC4_init(char *key, int key_size);
int RC4_dest(unsigned char *S);
int RC4_crypt(unsigned char *S, unsigned char *textbuffer, int textbuffer_size);
