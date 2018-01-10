#include <stdio.h>
#include "functions.h"

int main(int argc, char const *argv[]) {
	long i, *p;
	i = 0x0034deadbeef0020;
	p = &i;
	printf("%lx\n", cryptic_calculator(p));
	
	/*
	char s1[] = "1234";
	char s2[] = "5678";
	char *p1, *p2;
	p1 = s1;
	p2 = s2;
	my_memcpy(p1,p2,0);
	//swap_strs(p1,p2);
	printf("%s\n",p1);
	*/
  	return 0;
}
