#include <stdio.h>
#include <unistd.h>

int main() {
	int x = 1;
	pid_t pid;
	pid = fork();

	if (pid == 0) {
		x++;
		pid = getppid();
		printf("In child ID: %d\n",pid);
	}
	else {
		x--;
		printf("x: %d\n", x);
		sleep(1);
		pid = getppid();
		printf("In parent ID: %d\n",pid);
	}

	return 0;
}
