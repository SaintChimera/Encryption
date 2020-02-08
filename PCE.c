#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "algorithms/rc4.h"


void print_help(){
	printf("\n");
	printf("-a - sets the 'a' flag within the program\n");
	printf("-b - sets the 'b' flag within the program\n");
	printf("-c - fills the c buffer with the supplied data\n");
	printf("-h - prints this help message\n");
}


int main(int argc, char **argv){
	int aflag = 0;
	int bflag = 0;
	char *cvalue = NULL;
	int index;
	int c;

	opterr = 0;

	while ((c = getopt(argc, argv, "abch:")) != -1){
		switch (c){
			case 'a':
				aflag = 1;
				break;
			case 'b':
				bflag = 1;
				break;
			case 'c':
				cvalue = optarg;
				break;
			case 'h':
				print_help();
				return 0;
			case '?':
				if (optopt == 'c')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option '-%c'.\n",optopt);
				else
					fprintf(stderr,"Unknonw option character '\\x%x'.\n",optopt);
				return 1;
			default:
				abort();
		}
	}

	printf("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);

	// make the buffer for RC4, and some test strings
	char skey[] = "this key is more realistic";
	unsigned char stextbuffer[] = "this is a much larger sentence that i use for debugging";
	int pbkey_size = sizeof(char) * strlen(skey);
	int pbtextbuffer_size = sizeof(unsigned char) * sizeof(stextbuffer);
	char *pbkey = malloc(pbkey_size);
	unsigned char *pbtextbuffer = malloc(pbtextbuffer_size);
	
	// fill the buffer
	strncpy(pbkey,skey,pbkey_size);
	memcpy(pbtextbuffer,stextbuffer,pbtextbuffer_size);
	
	RC4(pbkey,pbkey_size,pbtextbuffer,pbtextbuffer_size); // encrypt

	for (int i = 0; i < pbtextbuffer_size; i++){
		printf("%x\n",pbtextbuffer[i]);
	}

	free(pbkey);
	free(pbtextbuffer);

	for (index = optind; index < argc; index++){
		printf("Non=option argument %s\n", argv[index]);
	}
}
