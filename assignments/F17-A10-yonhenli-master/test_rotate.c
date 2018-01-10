#include <stdio.h>

extern unsigned long rotate(unsigned long val, unsigned long num, unsigned long direction);

int main() {
	unsigned long ret = rotate(0xdeadbeefdeadbeef, 2, 1);
	printf("%lx\n", ret);
	ret = rotate(0xdeadbeefdeadbeef, 2, 0);
	printf("%lx\n", ret);
	ret = rotate(0xdeadbeefdeadbeef, 66, 1);
	printf("%lx\n", ret);
	ret = rotate(0x1, 1, 0);
	printf("%lx\n", ret);
	ret = rotate(0x45, 25, 1);
	printf("%lx\n", ret);
	ret = rotate(0x1, 64, 1);
	printf("%lx\n", ret);
	return 0;
}
