all: parser

scanner.cpp: scanner.l
	flex -o scanner.cpp scanner.l

parser.cpp parser.hpp: parser.y
	bison -v -d -o parser.cpp parser.y

parser: main.cpp scanner.cpp parser.cpp parser.hpp
	g++ -std=c++11 main.cpp scanner.cpp parser.cpp -o parser

clean:
	rm -f parser scanner.cpp parser.cpp parser.hpp parser.output
