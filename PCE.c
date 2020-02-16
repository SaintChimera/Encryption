#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "algorithms/rc4.h"


void print_help(){
	printf("\n");
	printf("-r - enables rc4 encryption.\n");
	printf("-k - keystring.\n");
	printf("-i - file to encrypt.\n");
	printf("-o - output file name. if this is not specified, a .enc extension is appended to the original file name.\n");
	printf("-h - prints this help message.\n");
}

// returns success or failure
int doRC4(char *skey, char *inf, char *outf){

	char mode[] = "r";
	FILE *fd = 0;
	unsigned char *buf = 0;
	unsigned char *RC4_context = 0;	
	int data_size;
	int bufsize = 4096;
	
	// open the file, make the buffer
	if ((fd = fopen(inf,mode)) == 0){
		fprintf(stderr,"Failure to open file");
		return 1;
	} else if ((buf = malloc(bufsize)) == 0){
		fprintf(stderr,"Failure to create buffer");
		return 1;
	}

	//unsigned char stextbuffer[] = "this is a much larger sentence that i use for debugging";
	//int pbtextbuffer_size = sizeof(unsigned char) * sizeof(stextbuffer);
	//unsigned char *pbtextbuffer = malloc(pbtextbuffer_size);
	
	// create key buffer, fill buffer
	int pbkey_size = sizeof(char) * strlen(skey);
	char *pbkey = malloc(pbkey_size);
	strncpy(pbkey,skey,pbkey_size);

	// init rc4
	if ((RC4_context = RC4_init(pbkey,pbkey_size)) == 0){
		fprintf(stderr,"Failure to init RC4\n");
		return 1;
	}

	// fill the buffer and encrypt
	while ((data_size = fread(buf,1,bufsize,fd)) > 0){
		if (RC4_crypt(RC4_context,buf,data_size) > 0){ // encrypt
			fprintf(stderr,"Failure to encrypt\n");
			return 1;
		}
	}

	if (RC4_dest(RC4_context) > 0){
		fprintf(stderr,"Failure to destroy context\n");
		return 1;
	}

	fclose(fd);
	free(pbkey);
	free(buf);

	return 0;
}

int main(int argc, char **argv){
	int rc4flag = 0;
	char *inf = NULL;
	char *outf = NULL;
	char *skey = NULL;
	int c;
//	int index;

	opterr = 0;

	while ((c = getopt(argc, argv, "rkioh:")) != -1){
		switch (c){
			case 'r':
				rc4flag = 1;
				break;
			case 'k':
				skey = optarg;
				break;
			case 'i':
				printf("%s\n",optarg);
				inf = optarg;
				break;
			case 'o':
				outf = optarg;
				break;
			case 'h':
				print_help();
				return 0;
			case '?':
				if (optopt == 'i' || optopt == 'o' || optopt == 'k')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option '-%c'.\n",optopt);
				else
					fprintf(stderr,"Unknown option character '\\x%x'.\n",optopt);
				return 1;
			default:
				abort();
		}
	}

	printf("rc4 = %d, key = %s, inf = %s, outf = %s\n", rc4flag, skey, inf, outf);

	if (inf == 0){
		fprintf(stderr,"No input file has been specified\n");
		return 1;
	}
	if (outf == 0){
		fprintf(stderr,"No output file has been specified\n");
		return 1;
	}

	if (rc4flag == 1){	
		skey = "key";
		if (doRC4(skey,inf,outf) > 1){
			fprintf(stderr,"Failed to encrypt with RC4\n");
		}
	}

//	for (index = optind; index < argc; index++){
//		printf("Non-option argument %s\n", argv[index]);
//	}
	return 0;
}
