CC = g++ 
exe = letters
$(exe): letters.o driver.o
	$(CC) letters.o driver.o -o $(exe)
letters.o: letters.cpp
	$(CC) -c letters.cpp
driver.o: driver.cpp
	$(CC) -c driver.cpp
clean: 
	rm -f *.out *.o $(exe)

exe_file = mult_div 
$(exe_file): mult_div.o prog.o
	$(CC) mult_div.o prog.o -o $(exe_file)
mult_div.o: mult_div.cpp
	$(CC) -c mult_div.cpp
prog.o: prog.cpp
	$(CC) -c prog.cpp
clean:
	rm -f *.out *.o $(exe_file)
