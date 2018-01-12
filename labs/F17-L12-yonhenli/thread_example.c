#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
char *input;

void *thread1(void *param) {
	pthread_mutex_lock(&m);

	input = malloc(sizeof(char));
	/*read a unspecified length string*/
    printf("Enter a string: ");
    int c;
    int i = 0;
    /* Read characters until found an EOF or newline character. */
    while((c = getchar()) != '\n' && c != EOF)
    {
        input[i++] = c;
        input = realloc(input, i+1);
    }
    input[i] = '\0';

	pthread_mutex_unlock(&m);
	return NULL;
}

void *thread2(void *param) {
	printf("Entered string: %s\n", input);
}

int main() {
	pthread_t tid1, tid2;
	pthread_create(&tid1, NULL, thread1, NULL);
	pthread_join(tid1, NULL);
	pthread_create(&tid2, NULL, thread2, NULL);
	pthread_join(tid2, NULL);

	free(input);

	return 0;
}