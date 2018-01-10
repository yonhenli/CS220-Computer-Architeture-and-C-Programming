#include "define.h"
#include <stdio.h>
int main(int argc, char const *argv[]) {
  		
	char s1[] = "1234127";
	char s2[] = "12";
	printf("%d\n", strrindex(s1, s2));
	
	char s[] = "10";
	printf("%d\n", is_int("-101"));
	printf("%d\n", is_int("-1"));
	printf("%d\n", is_int("-0"));
	printf("%d\n", is_int("0"));
	printf("%d\n", is_int("101"));
	printf("%d\n", is_int("-101"));

	printf("%d\n", is_int("01"));
	printf("%d\n", is_int("-a01"));
	printf("%d\n", is_int("a1"));
	printf("%d\n", is_int("-1a1"));
	printf("%d\n", is_int("101a"));
	
	struct point p1;
	struct point p2;

	p1.x = 1;
	p1.y = 1;
	p1.z = 1;

	p2.x = 2;
	p2.y = 2;
	p2.z = 2;
	
	printf("%lf\n", distance(p1,p2));
	return 0;
}
