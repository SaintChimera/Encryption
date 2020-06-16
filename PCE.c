#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "algorithms/rc4.h"


void print_help(){
    printf("\n");
    printf("-r - enables rc4 encryption.\n");
    printf("-k - keystring. printable ascii only.\n");
    printf("-i - file to encrypt.\n");
    printf("-o - output file name. if this is not specified, a .enc extension is appended to the original file name.\n");
    printf("-h - prints this help message.\n");
}

// returns success or failure
int doEncryption(char *skey, char *inf, char *outf, int (*initptr)(), int (*cryptptr)(), int (*destptr)()){

    char readmode[] = "r";
    char writemode[] = "w";
    FILE *fdin = NULL;
    FILE *fdout = NULL;
    unsigned char *buf = NULL;
    int data_size;
    int bufsize = 4096;
    int charsize = sizeof(char);
    
    // open the input file, make the buffer, open the output file
    if ((fdin = fopen(inf,readmode)) == 0){
        fprintf(stderr,"Failure to open input file\n");
        return 1;
    } 
    if ((buf = malloc(bufsize)) == 0){
        fprintf(stderr,"Failure to create buffer\n");
        return 1;
    }
    if ((fdout = fopen(outf,writemode)) == 0){
        fprintf(stderr,"Failure to open output file\n");
        return 1;
    }

    // create key buffer, fill buffer
    int pbkey_size = sizeof(char) * strlen(skey);
    char *pbkey = malloc(pbkey_size);
    strncpy(pbkey,skey,pbkey_size);

    // init rc4
    if (((*initptr)(pbkey,pbkey_size)) == 0){
        fprintf(stderr,"Failure to init RC4\n");
        return 0;
    }

    // fill the buffer and encrypt
    while ((data_size = fread(buf,charsize,bufsize,fdin)) > 0){
        if ((*cryptptr)(buf,data_size) == 0){ // encrypt
            fprintf(stderr,"Failure to encrypt\n");
            return 0;
        }
        if (fwrite(buf, charsize, data_size, fdout) == 0){ // write to file
            fprintf(stderr,"Failure to write to output file\n");
            return 0;
        }
    }

    if ((*destptr)() == 0){
        fprintf(stderr,"Failure to destroy context\n");
        return 0;
    }

    fclose(fdin);
    fclose(fdout);
    free(pbkey);
    free(buf);

    return 1;
}

int main(int argc, char **argv){

    int rc4flag = 0;
    char *inf = NULL;
    char *outf = NULL;
    char *skey = NULL;
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "rk:i:o:h")) != -1){
        switch (c){
            case 'r':
                rc4flag = 1;
                break;
            case 'k':
                skey = optarg;
                break;
            case 'i':
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
        if (doEncryption(skey,inf,outf, &RC4_init, &RC4_crypt, &RC4_dest) == 0){
            fprintf(stderr,"Failed to encrypt with RC4\n");
        }
    }

    return 0;
}
