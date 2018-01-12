#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
extern uint32_t *get_ebp(void);

void ret2libc(int dummy) {
	/*TASK 1*/
	uint32_t  *ebp_address = get_ebp();
	/*FIX*/
	ebp_address[2] = ebp_address[1];
	/*TASK 2*/
	ebp_address[1] = &system;
	/*TASK 3*/
	char *str = "/bin/bash";
	ebp_address[3] = str;

}

void ret2lib_generic(char* cmd) {
	/*TASK 1*/
	uint32_t  *ebp_address = get_ebp();
	/*FIX*/
	char *str = ebp_address[2];
	ebp_address[2] = ebp_address[1];
	/*TASK 2*/
	ebp_address[1] = &system;
	/*TASK 3*/
	ebp_address[3] = str;

}

int main() {
	//ret2libc(0);
	
	char *str = "ls";
	ret2lib_generic(str);
	printf("DONE!\n");
	return 0;
}
