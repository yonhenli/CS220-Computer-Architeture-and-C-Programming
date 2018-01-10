#include "functions.h"
#include <stdio.h>

int cryptic_calculator(void *payload){
	unsigned char *ptr = (unsigned char *)payload;
	if (*(ptr) == 0x2a) {
		short int byte3 = *(short int*)(ptr+2);
		short int byte5 = *(short int*)(ptr+4);
		short int byte7 = *(short int*)(ptr+6);
		return ((byte3)*(byte5)*(byte7));
	}

	else if (*(ptr) == 0x2f) {
		short int byte3 = *(short int*)(ptr+2);
		short int byte5 = *(short int*)(ptr+4);
		if (byte3 == 0) return 0xbad;
		return (byte5/byte3);
	}

	return 0xbad;
}

void my_memcpy(void *dst, void *src, unsigned int num_bytes){
	char *dptr = (char *) dst;
	char *sptr = (char *) src;

	int i = 0;

	for (i = 0; i < num_bytes; i++)
	{
		if (*(sptr+i) == '\0') break;
        if (*(dptr+i) == '\0') break;

		*(dptr+i) = *(sptr+i);
	}
}

void swap_strs(char *s1, char *s2){
	char temp;
	int i, length;
	i = length = 0;

	while(s1[i] != '\0') {
		length++;
		i++;
	}

	for (i = 0; i < length; i++) {
		temp = s2[i];
		s2[i] = s1[i];
		s1[i] = temp;
	}
}

