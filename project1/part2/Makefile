CFLAGS=-Wall -std=c99
LDLIBS=-lm

tri_sylvester_test: tri_sylvester_test.o tri_sylvester_solve.o
tri_sylvester_test.o: matrix.h
tri_sylvester_solve.o: matrix.h

.PHONY: clean run
clean:
		-$(RM) *.o tri_sylvester_test

run: tri_sylvester_test
		./tri_sylvester_test