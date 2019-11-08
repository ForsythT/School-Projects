CC = g++ 
exe = wumpus
$(exe):event.o empty.o wumpus.o bats.o pit.o gold.o rope.o player.o room.o game.o driver.o
	g++ event.o empty.o wumpus.o bats.o pit.o gold.o rope.o player.o game.o room.o driver.o -o wumpus
driver.o: driver.cpp
	g++ driver.cpp -c
game.o: game.cpp
	g++ game.cpp -c
room.o: room.cpp
	g++ room.cpp -c
player.o: player.cpp
	g++ player.cpp -c
rope.o: rope.cpp
	g++ rope.cpp -c
gold.o: gold.cpp
	g++ gold.cpp -c
pit.o: pit.cpp
	g++ pit.cpp -c
bats.o: bats.cpp
	g++ bats.cpp -c
wumpus.o: wumpus.cpp
	g++ wumpus.cpp -c
empty.o: empty.cpp
	g++ empty.cpp -c
event.o: event.cpp
	g++ event.cpp -c
clean:	
	rm -f a.out *.o wumpus
