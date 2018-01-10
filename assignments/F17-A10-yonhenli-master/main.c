#include <stdio.h>
#include "bt.h"

void f1() {
	print_backtrace(10);
}

void f2() {
	f1();
}

void f3() {
	f2();
}

void baz() {
	f3();
}

void bar() {
	baz();
}

void foo() {
	bar();
}

int main() {
	foo();
	return 0;
}
