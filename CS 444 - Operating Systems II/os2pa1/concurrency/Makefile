CC = gcc
exe_file = concurrency
$(exe_file): pthread_hello.o queue.o pubsub.o mersenne.o randomizationInterface.o rdrand.o
	$(CC) pthread_hello.o queue.o pubsub.o mersenne.o randomizationInterface.o rdrand.o -o $(exe_file) -lpthread

queue.o: queue.c
	$(CC) -c queue.c

pubsub.o: pubsub.c
	$(CC) -c pubsub.c

mersenne.o: mersenne.c
	$(CC) -c mersenne.c

pthread_hello.o: pthread_hello.c
	$(CC) -c pthread_hello.c

randomizationInterface.o: randomizationInterface.c
	$(CC) -c randomizationInterface.c

#specified flag compiles with gcc support for rdrand
rdrand.o: rdrand.c
	$(CC) -c -mrdrnd rdrand.c

debug: option += -D DEBUG
debug: $(exe_file)
clean:
	rm -f *.out *.o $(exe_file)
