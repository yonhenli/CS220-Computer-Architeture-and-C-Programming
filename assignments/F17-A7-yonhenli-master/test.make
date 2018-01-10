# Rule to build a test executable
# DO NOT MODIFY
test: test.c reverse64.S
	$(CC) -g -std=c99 $^ -o $@ -lcunit

# Rule to run *your* clean rule
# AND remove the test executable and output results
.PHONY: really-clean
really-clean: clean
	rm -fv test
