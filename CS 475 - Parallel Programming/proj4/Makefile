all: arraymult

simd.p4.o:	simd.p4.h  simd.p4.cpp
		g++  -c  simd.p4.cpp -o simd.p4.o

arraymult:	arraymult.cpp simd.p4.o
		g++  -o arraymult $(CFLAGS) arraymult.cpp simd.p4.o -lm  -fopenmp

clean:
	rm -f arraymult simd.p4.o
