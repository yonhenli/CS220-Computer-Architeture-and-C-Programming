CFLAGS := -std=c89 -g
all: driver

driver: driver.c reverse64.S
	gcc driver.c reverse64.S -m64 -std=c89 -g -o driver

.PHONY: clean
clean:
	rm -fv driver
	rm -fv *.o *~ \#*\# *.swp
include test.make
