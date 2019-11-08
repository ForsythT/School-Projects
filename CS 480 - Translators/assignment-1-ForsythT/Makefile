scan: scanner.o
	g++ scanner.o -o scan

scanner.o: scanner.cpp
	g++ -c scanner.cpp

scanner.cpp: scanner.l
	flex -o scanner.cpp scanner.l

clean:
	rm *.o *.cpp scan

