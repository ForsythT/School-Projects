all: compile test

parser.cpp parser.hpp: parser.y
	bison -d -o parser.cpp parser.y

scanner.cpp: scanner.l
	flex -o scanner.cpp scanner.l

compile: main.cpp ast.cpp parser.cpp scanner.cpp
	g++ -std=c++11 main.cpp `llvm-config-7.0-64 --cppflags --ldflags --libs --system-libs all` ast.cpp parser.cpp scanner.cpp -o compile

test: test.cpp python_compiler.o
	g++ test.cpp python_compiler.o -o test

python_compiler.o: compile
	compile < testing_code/p1.py > p1.ll

clean:
	rm -f compile test scanner.cpp parser.cpp parser.hpp *.o *.ll
