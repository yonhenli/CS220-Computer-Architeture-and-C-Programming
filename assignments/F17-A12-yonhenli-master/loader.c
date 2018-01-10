#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

int main(int argc, char *argv[]){

    typedef int (*Calc_fptr) (char, int, int);
	FILE *fp;
	unsigned int i;
	Calc_fptr calculator; 

    if (argc != 5) {
		printf("Usage %s <filename> <uint> <operation> <uint>\n", argv[0]);
        exit(1);
    }

    fp = fopen(argv[1], "rb");
    if (!fp) {
        printf("Cannot open file!");
        exit(0);
    }
    
    fseek(fp, 0L, SEEK_END);
    i = (unsigned int) ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    
	char *raw_bytes = (char *) malloc(1024);
    
    fread(raw_bytes, i, 1, fp);
    
    mprotect(raw_bytes, i, PROT_EXEC);
    mprotect(raw_bytes, i, PROT_READ);

	calculator = (Calc_fptr) raw_bytes;
	int result = calculator ((char)*argv[3], (int)atoi(argv[2]), (int)atoi(argv[4]));
	printf("%d %c %d = %d\n", atoi(argv[2]), *argv[3], atoi(argv[4]), result);
    
    fclose(fp);

	return 0;
}
