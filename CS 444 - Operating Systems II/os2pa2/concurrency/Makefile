CC = gcc
exe_file = dining
$(exe_file): dining.o mersenne.o randomizationInterface.o rdrand.o
	$(CC) dining.o mersenne.o randomizationInterface.o rdrand.o -o $(exe_file) -lpthread

mersenne.o: mersenne.c
	$(CC) -c mersenne.c

dining.o: dining.c
	$(CC) -c dining.c

randomizationInterface.o: randomizationInterface.c
	$(CC) -c randomizationInterface.c

#specified flag compiles with gcc support for rdrand
rdrand.o: rdrand.c
	$(CC) -c -mrdrnd rdrand.c

debug: option += -D DEBUG
debug: $(exe_file)
clean:
	rm -f *.out *.o $(exe_file)
