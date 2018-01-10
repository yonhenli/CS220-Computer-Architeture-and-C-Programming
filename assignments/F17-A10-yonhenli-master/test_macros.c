#include "macros.h"
#include <stdio.h>

int main() {
	unsigned long long  v,start,end,ret,i;
	v = 0xdeadbeefdeadbeef;
	start = 35;
	end = 32;
	
	/*
	unsigned long long temp1 = v >> end;
	unsigned long long temp2 = BIT_MASK(start - end);
	unsigned long long ans = temp1 & temp2;
	*/
	
	/*
	printf("temp1: %llu\n", temp1);
	printf("temp2: %llu\n", temp2);
	printf("ans: %llu\n", ans);
	*/

	i = TEST_IF_ANY_SET(0xdeadbeefdeadbeef,63,0);
	printf("%llu\n", i);

	i = TEST_IF_ALL_SET(0xdeadbeefdeadbeef,63,0);
	printf("%llu\n", i);

	i = TEST_IF_ANY_SET(0xdeadbeefdeadbeef,35,32);
	printf("%llu\n", i);

	i = TEST_IF_ALL_SET(0xdeadbeefdeadbeef,35,32);
	printf("%llu\n", i);

	i = TEST_IF_ANY_SET(0xdeadbeefdeadbeef,7,4);
	printf("%llu\n", i);

	i = TEST_IF_ALL_SET(0xdeadbeefdeadbeef,7,4);
	printf("%llu\n", i);

	i = TEST_IF_ALL_SET(0xdeadbeefdeadbeef,7,7);
	printf("all 7 7: %llu\n", i);

	i = TEST_IF_ANY_SET(0xdeadbeefdeadbeef,7,7);
	printf("any 7 7: %llu\n", i);

	i = TEST_IF_ANY_SET(0xdeadbeefdeadbeef,6,5);
	printf("any 1 0: %llu\n", i);

	i = TEST_IF_ALL_SET(0xdeadbeefdeadbeef,6,5);
	printf("all 1 0: %llu\n", i);

	return 0;
}
