CC=gcc
CFLAGS=-Wall -std=c99 -g
LDFLAGS=-L.
LDLIBS=-lopenblas

call_dgesv_test: call_dgesv_test.o call_dgesv.o
call_dgesv_test.o: matrix_io.h
call_dgesv.o: matrix_io.h

.PHONY: clean run
clean:
		-$(RM) *.o call_dgesv_test

run: call_dgesv_test
		./call_dgesv_test