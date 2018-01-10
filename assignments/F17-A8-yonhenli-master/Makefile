all: estimator toggle sorter

sorter: sorter.c driver.c
	gcc sorter.c driver.c -o driver

toggle: toggle.S toggle.c
	gcc toggle.c toggle.S -std=c89 -o toggle

estimator: estimator.S estimator.c 
	gcc estimator.c estimator.S -std=c89 -o estimator
	
.PHONY: clean
clean:
	rm -fv estimator
	rm -fv toggle
	rm -fv driver
	rm -fv *.o *~ \#*\# *.swp

include test.make
