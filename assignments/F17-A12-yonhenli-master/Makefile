all: loader hellosh

loader: loader.c
	gcc loader.c -m32 -std=c89 -g -Wl,-z,execstack -o loader
hellosh: hellosh.c
	gcc hellosh.c -o hellosh

.PHONY: clean
clean:
	rm -f loader hellosh
	rm -f *.txt
	rm -f *.o
	rm -f *~ \#*\# *.swp
