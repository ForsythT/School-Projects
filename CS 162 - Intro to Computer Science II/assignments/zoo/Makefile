CC = g++ 
exe = zootycoon
$(exe):animal.o tiger.o polarbear.o penguin.o monkey.o zoo.o game.o driver.o
	g++ animal.o tiger.o polarbear.o penguin.o monkey.o zoo.o game.o driver.o -o zootycoon
driver.o: driver.cpp
	g++ driver.cpp -c
game.o: game.cpp
	g++ game.cpp -c
zoo.o: zoo.cpp
	g++ zoo.cpp -c
monkey.o: monkey.cpp
	g++ monkey.cpp -c
penguin.o: penguin.cpp
	g++ penguin.cpp -c
polarbear.o: polarbear.cpp
	g++ polarbear.cpp -c
tiger.o: tiger.cpp
	g++ tiger.cpp -c
animal.o: animal.cpp
	g++ animal.cpp -c
clean:	
	rm -f a.out *.o blackjack
