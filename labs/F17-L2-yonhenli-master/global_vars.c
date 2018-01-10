#include <stdio.h>

char gfoo[x] = {0x10};

int main()
{
	printf("%p\n", &gfoo);
	return 0;
}
