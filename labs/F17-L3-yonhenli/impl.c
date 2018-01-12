#include<stdio.h>

struct bad_struct {
short s1;
long l1;
short s2;
};

struct good_struct {
short s1;
short s2;
long l1;
};

union unit {
char c;
int i;
long l;
};

int main() {
	struct good_struct gs;
	struct bad_struct bs;	
	union unit u;
	/*
	printf("size of bs: %d\n", sizeof(bs));
	printf("size of gs: %d\n", sizeof(gs));

	printf("address of s1: %p\n", &bs.s1);
	
	printf("address of l1: %p\n", &bs.l1);
	
	printf("address of s2: %p\n", &bs.s2);


	printf("address of s1: %p\n", &gs.s1);
	
	printf("address of l1: %p\n", &gs.l1);
	
	printf("address of s2: %p\n", &gs.s2);
	*/
	scanf("%lu", &u.l);

	printf("size of u: %d\n", sizeof(u));
	printf("%c, %lu, %d, %s\n", u.c, u.l, u.i, &u.l);
	
	/*
	printf("address of c: %p\n", &u.c);

	printf("address of i: %p\n", &u.i);
	
	printf("address of l: %p\n", &u.l);
	*/

}
