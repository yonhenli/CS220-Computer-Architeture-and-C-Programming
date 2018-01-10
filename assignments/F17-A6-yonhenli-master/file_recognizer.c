#include "file_recognizer.h"
#include <stdio.h>

void get_file_type(FILE *fptr) {
	int i,j,ctr = 0;
	unsigned char buffer[8];
	
	fread(&buffer, 1, 8, fptr);

	for (i = 0; i < 7; i++) {
		for (j = 0; j < name_list[i].num; j++) {
			if (name_list[i].signiture[j] ==  buffer[j]){			
				ctr++;
			}
		}

		if (j == ctr) {
			printf("%s\n", name_list[i].type);
			fclose(fptr);
			return;
		}

		ctr = 0;
	}
	
	printf("%s\n", "File type unknown.");
	
	fclose(fptr);
	return;	
}

int main(int argc, char const *argv[]) {
	if (argc != 2) {
		printf("%s\n", "Invalid input.");
		return 0;
	}
	
	FILE *fptr = fopen(argv[1], "rb");;
	int retVal = 0;
	
	if (fptr == NULL) {
		printf("%s\n", "Invalid input.");
		return 0;
	}
	
	get_file_type(fptr);
	
	return 0;
}
