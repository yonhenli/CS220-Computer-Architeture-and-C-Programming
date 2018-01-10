#include <stdio.h>
#include "toggle.h"

/*
unsigned long toggle_bit(unsigned long num, unsigned long bit_num) {
	if (bit_num < 0 || bit_num > 63) return 0;
	num = num ^(1 << bit_num);
	return num;
}
*/

int main() {
	int j = toggle_bit(66,6);
	printf("%d\n", j);

	return 0;
}
