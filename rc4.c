/*https://paginas.fe.up.pt/~ei10109/ca/rc4.html
 *
 */

#include <stdio.h>
#include <string.h>

# define N 256 // S size

void swap(unsigned char *a, unsigned char *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int Key_Scheduling_Algorithm(char *key, unsigned char *S) // generates a permutation of all possible  bytes based on the input key.
{
	int len = strlen(key);
	int j=0;
	for(int i=0; i<N; i++){ // seed S with 0 - 255
		S[i] = i;
	}
	for(int i=0; i<N; i++){
		j = (j + S[i] + key[i%len]) % N;	// permute S with j(persistent), S[i], and a byte from the key. then mod N(8 bits)
		swap(&S[i],&S[j]); // swap the character at the position represented by j, with the one represented by i
	}
	return 0;
}

int Pseudo_Random_Generation_Algorithm(unsigned char *S, char *plaintext, char *ciphertext)
{
	int i = 0; // incrementer mod 256
	int j = 0; // changes to permute S each round
	for(size_t n=0, len = strlen(plaintext); n < len; n++){
		i = (i+1) % N; // its import to increment i before starting anything else
		j = (j + S[i]) % N; // change j

		swap(&S[i], &S[j]); // permute S. its important that this happens before xor encryption
		int rnd = S[(S[i] + S[j]) % N]; // select byte to xor against plaintext 
		ciphertext[n] = rnd ^ plaintext[n]; // xor
	}
	return 0;
}

int main()
{
	unsigned char S[N];
	char *plaintext = "different";
	char *key = "key";
	size_t plaintext_len = strlen(plaintext);
	char ciphertext[plaintext_len];
	printf("%s\n",key);
	printf("plaintext len: %zu\n",plaintext_len);
	
	int KSA_return = Key_Scheduling_Algorithm(key, S);
	int PRGA_return = Pseudo_Random_Generation_Algorithm(S, plaintext, ciphertext);

	for(size_t i=0; i<=plaintext_len; i++){
		printf("ciphertext len: %zu\n",plaintext_len);
		printf("%x\n",ciphertext[i]);
	}

	return 0;
}
