#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>

int main() {
	char *prog = "./runner";
	/*TODO*/
	char *args[] = {};
	if (fork() == 0) {
		printf("Child pid = %d, parent pid = %d\n", getpid(), getppid());
		execvp(prog,args);
		fprintf(stderr, "exec: %s\n", strerror(errno));
	}
	else {
		wait(NULL);
	}

	return 0;
}
