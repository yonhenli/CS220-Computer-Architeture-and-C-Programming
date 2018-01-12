
all: prelim ret2libc

prelim: prelim.c
	gcc prelim.c -m32 -o prelim

ret2libc: ret2libc.c get_ebp.S
	gcc ret2libc.c get_ebp.S -m32 -o ret2libc

clean:
	rm -f prelim
	rm -f ret2libc
