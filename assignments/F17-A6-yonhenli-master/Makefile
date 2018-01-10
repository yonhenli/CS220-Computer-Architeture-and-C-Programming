CFLAGS:= -g -Wall

all: file_recognizer

file_recognizer: file_recognizer.c
	gcc file_recognizer.c -o file_recognizer

.PHONY: clean
clean:
	rm -fv file_recognizer
	rm -fv *.o *~ \#*\# *.swp

# test.make contains the test suite for grading.
# We will provide it then. For now, it doesn't do much.
include test.make
