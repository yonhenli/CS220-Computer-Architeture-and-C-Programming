# OPTIONAL: Set these variables as required.
CFLAGS := -g -Wall -std=c99
LDFLAGS :=
LDLIBS :=

all: static-driver driver

# OPTIONAL: COMPLETE THIS TARGET
# This target produces an object file for making libraries.
parser.o : parser.c
	gcc -c -fPIC $(CFLAGS) parser.c

# COMPLETE THIS TARGET
# This target produces the dynamic library.
lib/libparser.so: parser.o
	gcc -shared -fPIC -o libparser.so parser.o 
	mv libparser.so ./lib

# COMPLETE THIS TARGET
# This target produces the executable using the dynamic library
driver:	driver.c lib/libparser.so
	gcc -g driver.c -I$(PWD) -L$(PWD)/lib -o driver -lparser

# This target produces the executable using static library
static-driver: driver.c lib/libparser.a
	$(CC) $(CFLAGS) driver.c -I$(PWD) lib/libparser.a -o static-driver

.PHONY: clean
clean:
	rm -fv static-driver driver
	rm -fv lib/libparser.so
	rm -fv *.o *.txt *.bin
	rm -fv *~ \#*\# *.swp


# Add testing targets. See the file.
# Doesn't currently do anything.
include test.make
