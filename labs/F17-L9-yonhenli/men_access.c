#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdlib.h>
#include <malloc.h>
#define STEP_SIZE 1024
#define READ_SIZE 64*1024*1024
#define PAGE_SIZE 4096
#define NG 128
#define PAGES_IN_NG (NG*1024*1024)/PAGE_SIZE

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

void test_hdd(){
	int fp;
	fp=open("file64M", O_RDONLY);
	struct timeval tvDiff, tvStar, tvEnd;
	char *c;

	gettimeofday(&tvStar, NULL);
	for(int i=0; i<READ_SIZE; i+=STEP_SIZE){
		read(fp, &c[0],STEP_SIZE);
	}
	gettimeofday(&tvEnd,NULL);

	timeval_subtract(&tvDiff,&tvEnd, &tvStar);
	timeval_print("HDD ACCESS: ", &tvDiff);
	close(fp);
}

void test_mem(){
	unsigned char *mem_arr[PAGES_IN_NG];

	struct timeval tvDiff, tvStar, tvEnd;
	for (int i=0;i<PAGES_IN_NG; i++){
		if((mem_arr[i]=memalign(PAGE_SIZE, PAGE_SIZE))==NULL){
			printf("Malloc failed");
		}
	}
	
	gettimeofday(&tvStar, NULL);

	for(int i=0; i< PAGES_IN_NG;i++){
		for(int j=0; j< PAGE_SIZE;j++){
			mem_arr[i][j]++;
		}
	}

	gettimeofday(&tvEnd,NULL);
	timeval_subtract(&tvDiff,&tvEnd, &tvStar);
	timeval_print("MEN SERIAL ACCESS: ", &tvDiff);

	gettimeofday(&tvStar, NULL);
	for(int i=0; i< PAGE_SIZE;i++){
		for(int j=0; j< PAGES_IN_NG;j++){
			mem_arr[j][i]++;
		}
	}

	gettimeofday(&tvEnd,NULL);

	timeval_subtract(&tvDiff,&tvEnd, &tvStar);
	timeval_print("MEN SERIAL ACCESS: ", &tvDiff);
}

int main(){
	test_hdd();
	test_mem();
	return 0;

}
