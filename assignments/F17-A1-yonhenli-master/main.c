// main.c

#include "functions.h"
#include<stdio.h>

int main(int argc, char **argv) {
	int result;
	int num;
	printf("please enter a number: ");
	scanf("%d", &num);
	result = isFib(num);
	printf("the input is the %dth fib \n", result);

	printf("-----------------------\n");
	
	unsigned long i;
	unsigned int result8;
	printf("please enter a number: "); 
	scanf("%lu", &i);
	result8 = count_vowels(i);
	printf("%d has %d vowels\n", i, result8);

	printf("-----------------------\n");
	long input;
	unsigned int result1;

	printf("please enter a number: ");
	scanf("%ld", &input);
	result1 = count_ones(input);
	printf("amount of 1s: %d\n", result1);

	printf("-----------------------\n");
	int a;
	int b;
	long result2;
	printf("please enter a number a: ");
	scanf("%d", &a);
	printf("please enter a number b: ");
	scanf("%d", &b);
	result2 = a4_minus_b4(a,b);

	printf("a^4 - b^4 =: %ld\n", result2);
  return 0;
}
