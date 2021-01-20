CFLAGS=-Wall -std=c99
LDLIBS=-lm

fwdsub_test: fwdsub_test.o fwdsub.o
fwdsub_test.o: fwdsub.h
fwdsub.o: fwdsub.h

.PHONY: clean run
clean:
		-$(RM) *.o fwdsub_test

run: fwdsub_test
		./fwdsub_test