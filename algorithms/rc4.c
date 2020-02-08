/*https://paginas.fe.up.pt/~ei10109/ca/rc4.html
 *
 */

#include <stdio.h>
#include <string.h>

# define N 256 // S box size

void swap(unsigned char *a, unsigned char *b){
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int Key_Scheduling_Algorithm(char *key, int key_size, unsigned char *S) // generates a permutation of all possible  bytes based on the input key.
{
	int j=0;
	for(int i=0; i<N; i++){ // seed S with 0 - 255
		S[i] = i;
	}
	for(int i=0; i<N; i++){
		j = (j + S[i] + key[i%key_size]) % N;	// permute S with j(persistent), S[i], and a byte from the key. then mod N(8 bits)
		swap(&S[i],&S[j]); // swap the character at the position represented by j, with the one represented by i
	}
	return 0;
}

int Pseudo_Random_Generation_Algorithm(unsigned char *textbuffer, int textbuffer_size, unsigned char *S)
{
	int i = 0; // incrementer mod 256
	int j = 0; // changes to permute S each round
	int rnd = 0;
	for(size_t n=0; n < textbuffer_size; n++){
		i = (i+1) % N; // its important to increment i before starting anything else
		j = (j + S[i]) % N; // change j

		swap(&S[i], &S[j]); // permute S. its important that this happens before xor encryption
		rnd = S[(S[i] + S[j]) % N]; // select byte to xor against plaintext 
		textbuffer[n] = rnd ^ textbuffer[n]; // xor
	}
	return 0;
}

int RC4(char *key, int key_size, unsigned char *textbuffer, int textbuffer_size)
{
	unsigned char S[N];
	
	if(Key_Scheduling_Algorithm(key, key_size, S) > 0){
		return 1;
	}
	if(Pseudo_Random_Generation_Algorithm(textbuffer, textbuffer_size, S) > 0){
		return 1;
	}
	return 0;
}
