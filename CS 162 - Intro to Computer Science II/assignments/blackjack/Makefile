CC = g++ 
exe = blackjack
$(exe):deck.o card.o hand.o player.o dealer.o game.o driverb.o
	g++ deck.o card.o hand.o player.o dealer.o game.o driverb.o -o blackjack
driverb.o: driverb.cpp
	g++ driverb.cpp -c
game.o: game.cpp
	g++ game.cpp -c
dealer.o: dealer.cpp
	g++ dealer.cpp -c
player.o: player.cpp
	g++ player.cpp -c
hand.o: hand.cpp
	g++ hand.cpp -c
deck.o: deck.cpp
	g++ deck.cpp -c
card.o: card.cpp
	g++ card.cpp -c
clean:	
	rm -f a.out *.o blackjack
