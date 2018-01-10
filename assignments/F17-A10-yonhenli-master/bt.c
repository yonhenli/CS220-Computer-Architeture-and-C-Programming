#include <stdio.h>
#include "bt.h"

extern unsigned long long *asm();

void print_backtrace(int count)
{
	int times = 1;
	unsigned long long ret_addr;
	unsigned long long *curr_rbp = asm();

	/*find the range of main*/
	unsigned char *main_end = (unsigned char *)(&main);
	while (*main_end != 0xc3) (main_end) ++;

	while (count > 0)
	{
		ret_addr = (unsigned long long) *(curr_rbp + 0x1);

		printf("#%d\t0x%016llx\n", times, ret_addr);

		if ((unsigned long long)&main < ret_addr && ret_addr < (unsigned long long)&main_end)
			return;

		curr_rbp = (unsigned long long*)*(curr_rbp);
		count--;
		times++;
	}
}
