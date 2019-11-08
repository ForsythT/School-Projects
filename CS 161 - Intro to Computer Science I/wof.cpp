/***********************************************************************************
** Program: wof.cpp
** Author: Tim Forsyth
** Date: 2/05/2016
** Description: Plays the game Wheel of Fortune with up to 3 players
** Input: Number of players, number of rounds, messages for each rounds, 
**	  guesses for vowels/non vowels/puzzles
** Output: Wheel of Fortune Game - Money won, scoreboard each round, end game total
***********************************************************************************/

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cmath>

using namespace std;

void makeLower(string&);
void convertMessage(string&, string&, int i);
void getPuzzle(string&, int i);
void gameSetup(int&, int&);
void roundSetup(string&, string&, int, int&, int,int*, int*);
void printMessage(string);
void playGame(string&, int);
void getPlayers(int&);
void getRounds(int&);
void spinWheel(int*, int, int, int&, string, string&);
void spinScores(int*, int, int, int);
void playerDecision(int*, int, int, int&, int&, string, string&, string&, bool&);
void roundTurn(int*, int&, int&, int&, string, string&);
void turnContinue(bool&, int*, int, int, int&, int&, string&, string, string&);
void guessLetter(int, int, int*, int&, string, string&);
void nonVowelCheck(int, int, int*, int&, char&, string, string&);
void convertChar(int, int, int*, int&, string&, char&, string, string&);
void vannaWhite(int, int, int*, int&, char, string, string&);
void invalidOption(bool&, int*, int, int, int&, int&, string, string&, string&);
void solvePuzzle(string&, string, string&, int*, int, int&, bool&);
void solveScores(string, int*, int);
char buyVowel(int*, int, int, int&, int&, string, string&, string&, bool&);
bool restart();
char getChar();
char getVowel(string, int*, int, int, int&, int&, string, string&, string&, bool&);
void scoreboard(int*, int);
void scoreboardFinal(int*, int);
void winner(int*, int);
void addScores(int*, int*, int);
void resetScores(int*, int);
bool checkBalance(int*, int, int, int&, int&, string, string&, string&, bool&);
int checkInt(string, int&);

int main(){
	int players, rounds, spin, *scores, *scoretotal;
	string puzzle, alias;
	bool cont = true;
	srand(time(NULL));
	do{
		gameSetup(players, rounds);
		scores = new int[players - 1];
		scoretotal = new int[players - 1];
		roundSetup(puzzle, alias, rounds, spin, players, scores, scoretotal);
		scoreboardFinal(scoretotal, players);
		winner(scoretotal, players);
	}while(cont == restart());
}

void winner(int *scores, int players){
	int winner = 0;
	int x = 0;
	for(int i = 0; i < players; i++){
		if(scores[i] > winner){
			winner = scores[i];
			x = i + 1;
		}
	}
	cout << "The winner is Player " << x << " with $" << winner << "!" << endl;
	cout << endl;
}	

bool restart(){
	char again;
	while(true){
		again = getChar();
		switch(again){
			case '1':
				return true;
			case '2': 	
				return false;
			default:
				cout << "Invalid input." << endl;
				break;
		}
	}
}

char getChar(){
	string again;
	char cont;
	while(true){
		cout << "Do you want to play again?\nYes - 1\nNo - 2" << endl;
		cin >> again;
		if(again.length() == 1){
			cont = again.at(0);
			return cont;
		}
		else{
			cout << "Invalid input." << endl;
		}
	}
}

void gameSetup(int &players, int &rounds){
	system("clear");
	cout << "Welcome to Wheel Of Fortune!" << endl;
	getPlayers(players);
	getRounds(rounds);
}

void getPlayers(int &players){
	string playerstr;
	cout << "How many players are there? ";
	cin >> playerstr;
	players = checkInt(playerstr, players);
}	

int checkRounds(string str, int &rounds){
	char numchar;
	string num;
	int i;	
	if(str.length() == 1){
		numchar = str.at(0);
		if(numchar >= '1'){
			num = numchar;
			return atoi(num.c_str());
		}
		else{ 
			cout << endl << "Invalid input. Enter a positive integer number." << endl << endl;
			getRounds(rounds);
		}
	}
	else{
		cout << endl << "Invalid input. Enter a positive integer number." << endl << endl;    	
		getRounds(rounds);
	}
}

int checkInt(string str, int &players){
	char numchar;
	string num;
	int i;	
	if(str.length() == 1){
		numchar = str.at(0);
		if(numchar >= '1' && numchar <= '3'){
			num = numchar;
			return atoi(num.c_str());
		}
		else{ 
			cout << endl << "Invalid input. This game can be played with up to 3 players. (1, 2 or 3)" << endl << endl;
			getPlayers(players);
		}
	}
	else{
		cout << endl << "Invalid input. This game can be played with up to 3 players. (1, 2 or 3)" << endl << endl;    	
		getPlayers(players);
	}
}

void getRounds(int &rounds){
	string roundstr;
	cout << "How many rounds would you like to play? ";
	cin >> roundstr;
	rounds = checkRounds(roundstr, rounds);	
}

void getPuzzle(string &puzzle, int i){
	cout << "Enter a message: ";
	if(i == 0)
		getline(cin.ignore(), puzzle);
	else
		getline(cin, puzzle);
}

void roundSetup(string &puzzle, string &alias, int rounds, int &spin, int players, int *scores, int *scoretotal){
	int count = 0;
	for(int i = 0; i < rounds; i++){
		cout << endl << "Preparing for round " << (i + 1) << "..." << endl;
		convertMessage(puzzle, alias, i);
		system("clear");
		cout << "* * * * * * * * * *" << endl;
		cout << endl << "* * * Round " << (i + 1) << " * * *" << endl << endl;
		cout << "* * * * * * * * * *" << endl << endl;	
		scoreboard(scoretotal, players);
		cout << "* * * * * * * * * *" << endl << endl;
		roundTurn(scores, count, players, spin, puzzle, alias);
		addScores(scores, scoretotal, players);
		resetScores(scores, players);
	}
}

void resetScores(int *scores, int players){
	for(int i = 0; i < players; i++){
		scores[i] = 0;
	}
}

void addScores(int *scores, int *scoretotal, int players){
	for(int i = 0; i < players; i++){
		scoretotal[i] += scores[i];
	}
}

void scoreboardFinal(int *scoretotal, int players){
	cout << endl << "* * * * * * * * * * *" << endl;
	cout << endl << "* * * * Final * * * *" << endl;
	cout << endl << "* * * * * * * * * * *" << endl;
	for(int i = 0; i < players; i++){
		cout << endl << "* * Player " << (i + 1) << ": $" << scoretotal[i] << endl;
	}
	cout << endl << "* * * * * * * * * * *" << endl;
}

void scoreboard(int *scores, int players){	
	for(int i = 0; i < players; i++){
		cout << "* * Player " << (i + 1) << ": $" << scores[i] <<  endl << endl;
	}
}

void printMessage(string alias){
	cout << endl << "The message is " << alias << endl << endl;
}

void convertMessage(string &puzzle, string &alias, int i){
	getPuzzle(puzzle, i);
	alias = puzzle;
	makeLower(alias);
	for(int i = 0; i < alias.length(); i++)
		if(alias.at(i) >= 'a' && alias.at(i) <= 'z'){
			alias.at(i) = '-';
		}
		else if(alias.at(i) >= '0' && alias.at(i) <= '9'){
			convertMessage(puzzle, alias, i);
		}
		else{
		}
}

void makeLower(string &alias){
	for(int i = 0; i < alias.length(); i++)
		alias.at(i) = tolower(alias.at(i));
}

void spinWheel(int *scores, int players, int i, int &count, int &spin, string puzzle, string &alias){
	spin = rand()%22;
	cout << "You got " << spin << "!" << endl;
	if(spin != 0 && spin != 21){
		guessLetter(spin, i, scores, count, puzzle, alias);
		return;
	}
	else if(spin == 21){
		cout << "Oh no! I'm sorry, you lost your turn. Total earnings: $" << scores[i] << endl;
		count = 0;
	}
	else{
		scores[i] = 0;
		cout << "Oh no! You've gone bankrupt! Total earnings: $" << scores[i] << endl;
		count = 0;
	}
}
void playerDecision(int *scores, int players, int i, int &count, int &spin, string puzzle, string &alias, string &compare, bool &wrong){
	string decisionstr;
	char decision, vowel;
	cout << "Do you want to: \n1 - Spin the Wheel\n2 - Solve the Puzzle\n3 - Buy a Vowel\n";
	cin >> decisionstr;
	cout << endl;
	if(decisionstr.length() == 1){
		decision = decisionstr.at(0);
		if(decision == '1'){
			spinWheel(scores, players, i, count, spin, puzzle, alias);
			return;
		}
		else if(decision == '2'){
			solvePuzzle(compare, puzzle, alias, scores, i, count, wrong);
			return;
		}
		else if(decision == '3'){
			if (checkBalance(scores, players, i, count, spin, puzzle, alias, compare, wrong) == true)
				return;
			vowel = buyVowel(scores, players, i, count, spin, puzzle, alias, compare, wrong);
			vannaWhite(spin, i, scores, count, vowel, puzzle, alias);
			return;
		}
		else
			invalidOption(wrong, scores, players, i, count, spin, puzzle, alias, compare);
	}
	else
		invalidOption(wrong, scores, players, i, count, spin, puzzle, alias, compare);
}

void invalidOption(bool &wrong, int *scores, int players, int i, int &count, int &spin, string puzzle, string &alias, string &compare){
	cout << "Invalid option. Enter either 1, 2 or 3." << endl;
	playerDecision(scores, players, i, count, spin, puzzle, alias, compare, wrong);
}

bool checkBalance(int *scoretotal, int players, int i, int &count, int &spin, string puzzle, string &alias, string &compare, bool &wrong){
	if(scoretotal[i] < 10){
		cout << "You don't have enough money to buy a vowel." << endl;
		playerDecision(scoretotal, players, i, count, spin, puzzle, alias, compare, wrong);
		return true;
	}
	else
		return false;
}

char buyVowel(int *scoretotal, int players, int i, int &count, int &spin, string puzzle, string &alias, string &compare, bool &wrong){
	string decisionstr;
	char vowel;
	string potVowel;	
	cout << "Guess a vowel: ";
	cin >> potVowel;
	vowel = getVowel(potVowel, scoretotal, players, i, count, spin, puzzle, alias, compare, wrong);
	return vowel;
}

char getVowel(string potVowel, int *scores, int players, int i, int &count, int &spin, string puzzle, string &alias, string &compare, bool &wrong){
	char vowel;
	if(potVowel.length() == 1)
		vowel = potVowel.at(0);
		if(vowel == 'a' || vowel == 'e' || vowel == 'i' || vowel == 'o' || vowel == 'u')
			return vowel;
		else
			cout << "Invalid input. Enter a vowel! (a, e, i, o, u)" << endl;
			buyVowel(scores, players, i, count, spin, puzzle, alias, compare, wrong);
	string decisionstr;
}

void roundTurn(int *scores, int &count, int &players, int &spin, string puzzle, string &alias){
	bool wrong = false;
	string compare = puzzle;
	do{
		for(int i = 0; i < players; i++){
			printMessage(alias);
			cout << "Player " << (i + 1) << ":" << endl;
			playerDecision(scores, players, i, count, spin, puzzle, alias, compare, wrong);
			if(count > 0 && alias != puzzle)
				turnContinue(wrong, scores, players, i, count, spin, alias, puzzle, compare);
			if(alias == puzzle)
				break;
		}
	}while(alias != puzzle);
}

void turnContinue(bool &wrong, int *scores, int players, int i, int &count, int &spin, string &alias, string puzzle, string &compare){
	while(count > 0 && alias != puzzle){
		printMessage(alias);
		playerDecision(scores, players, i, count, spin, puzzle, alias, compare, wrong);	
	}
}

void solveScores(string guess, int *scores, int i){
	for(int x = 0; x < guess.length(); x++){
		if(guess.at(x) == '-'){
			scores[i] += 5;
		}	
	}
}

void solvedPuzzle(string &alias, string puzzle){
	alias = puzzle;
}

void solvePuzzle(string &compare, string puzzle, string &alias, int *scores, int i, int &count, bool &wrong){
	string guess;
	getPuzzle(guess, 0);
	makeLower(guess);
	makeLower(alias);
	makeLower(compare);
	if(guess == compare){
		guess = alias;
		solveScores(guess, scores, i);
		solvedPuzzle(alias, puzzle);
		cout << endl << "That is correct! Total earnings: $" << scores[i] << endl << endl;
		cout << "Player " << i + 1 << " has won the round!" << endl;
	}	
	else{
		cout << endl << "Sorry, you are incorrect." << endl;
		count = 0;	
	}
}

void guessLetter(int spin, int i, int *scores, int &count, string puzzle, string &alias){
	string potLetter;
	char letter;
	cout << "Guess a letter: ";
	cin >> potLetter;
	convertChar(spin, i, scores, count, potLetter, letter, puzzle, alias);
	if(letter >= 'a' && letter <= 'z' && letter != 'a' && letter != 'e' && letter != 'i' & letter != 'o' && letter != 'u'){
		vannaWhite(spin, i, scores, count, letter, puzzle, alias);
	}
}

void convertChar(int spin, int i, int *scores, int &count, string &potentialLetter, char &letter, string puzzle, string &alias){
	if(potentialLetter.length() == 1){
		letter = potentialLetter.at(0);
		nonVowelCheck(spin, i, scores, count, letter, puzzle, alias);	
		return;
	}
	else{
		cout << "Invalid input. Enter a non-vowel letter." << endl;
		guessLetter(spin, i, scores, count, puzzle, alias);
	}
}

void nonVowelCheck(int spin, int i, int *scores, int &count, char &letter, string puzzle, string &alias){
	letter = tolower(letter);
	if(letter >= 'a' && letter <= 'z'){
		if(letter == 'a' || letter == 'e' || letter == 'i' || letter == 'o' || letter == 'u'){
			cout << "Invalid input. Enter a non-vowel letter." << endl;
			guessLetter(spin, i, scores, count, puzzle, alias);	
		}
		else
			return;
	}
	else{
		cout << "Invalid input. Enter a non-vowel letter." << endl;
		guessLetter(spin, i, scores, count, puzzle, alias);
	}
}

void vannaWhite(int spin, int x, int *scores, int &count, char letter, string puzzle, string &alias){
	count = 0;	
	for(int i = 0; i < puzzle.length(); i++){
		if(tolower(puzzle.at(i)) == letter){
			alias.at(i) = puzzle.at(i);
			count += 1;
		}
	}
	if(letter != 'a' && letter != 'e' && letter != 'i' && letter != 'o' && letter != 'u'){
		spinScores(scores, spin, x, count);
	}
	else{
		scores[x] -= 10;
	}
	cout << count << " found. Total earnings: $" << scores[x] << endl;
}

void spinScores(int *scores, int spin, int i, int count){
	if(spin == 0){
		scores[i] = 0;
	}
	else if(spin == 21){
	}
	else
		scores[i] = scores[i] + (count * spin);
}
