#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>

#define LOOPS 10 
#define TIMES 1000000

extern void NOP_operations();
extern void NOP_none();

int timeval_subtract(struct timeval *result, struct timeval *t2, struct timeval *t1)
{
    long int diff = (t2->tv_usec + 1000000 * t2->tv_sec) - (t1->tv_usec + 1000000 * t1->tv_sec);
    result->tv_sec = diff / 1000000;
    result->tv_usec = diff % 1000000;

    return (diff<0);
}

void timeval_print(char *str, struct timeval *tv)
{
    printf("%s %ld sec, %06ld micro sec\n", str, tv->tv_sec, tv->tv_usec);
}

int main()
{
	struct timeval tvDiff, tvDiff_nope, tvDiff_ret, tvStart, tvEnd;
	int i ,j = 0;
	double accum = 0;

	for (i = 0; i < LOOPS; i ++){
		gettimeofday(&tvStart, NULL);
		for (j = 0; j < TIMES; j++){
			NOP_operations();
		} 
		gettimeofday(&tvEnd, NULL);
		timeval_subtract(&tvDiff_nope, &tvEnd, &tvStart);
		/*timeval_print("100 NOPE: ", &tvDiff_nope);*/
		
		gettimeofday(&tvStart, NULL);
		for (j = 0; j < TIMES; j++) {
			NOP_none();
		}
		gettimeofday(&tvEnd, NULL);
		timeval_subtract(&tvDiff_ret, &tvEnd, &tvStart);
		
		/*timeval_print("000 NOPE: ", &tvDiff_ret);*/

		timeval_subtract(&tvDiff, &tvDiff_nope, &tvDiff_ret);
		accum += tvDiff.tv_sec * 1000000 + tvDiff.tv_usec;
	}

	printf("%.2e\n", TIMES*100000000LL / (accum/LOOPS));

	return 0; 
}
