/*
 * MinimaxPlayer.cpp
 *
 *  Created on: Apr 17, 2015
 *      Author: wong
 */
#include <iostream>
#include <assert.h>
#include "MinimaxPlayer.h"

using std::vector;

MinimaxPlayer::MinimaxPlayer(char symb) :
	Player(symb) {

}

MinimaxPlayer::~MinimaxPlayer() {

}

int MinimaxPlayer::util(OthelloBoard *board){
	int p1_score = board->count_score(board->get_p1_symbol());
	int p2_score = board->count_score(board->get_p2_symbol());
	return p1_score - p2_score;
}

vector<OthelloBoard*> MinimaxPlayer::succ(char symb, OthelloBoard *board){
	vector<OthelloBoard*> succBoards;
	int boardSize = 4; // 4x4 board

	for(int i = 0; i < boardSize; i++){
		for(int j = 0; j < boardSize; j++){
			// If the move is legal...
			if(board->is_legal_move(i, j, symb)){
				// Add move to succBoards
				succBoards.push_back(new OthelloBoard(*board));
				succBoards.back()->play_move(i, j, symb);
				succBoards.back()->setCol(i);
				succBoards.back()->setRow(j);
			}
		}
	}
	// Return the vector of successor boards
	return succBoards;
}

int MinimaxPlayer::minValue(int &row, int &col, OthelloBoard *board){
	vector<OthelloBoard*> succBoards;
	int minVal = 1000000;

	// Check if the board is at a terminal state (no legal moves left)
	if((board->has_legal_moves_remaining('X') == false) && (board->has_legal_moves_remaining('O') == false)){
		return util(board);
	}

	// If not, find succBoards and continue recursively
	int newRow = 0;
	int newCol = 0;
	int val;
	int idx = 0;

	succBoards = succ('O', board);

	for(int i = 0; i < succBoards.size(); i++){
		val = maxValue(row, col, succBoards[i]);
		if(val < minVal){
			newRow = succBoards[i]->getRow();
			newCol = succBoards[i]->getCol();
			minVal = val;
			idx = i;
		}
		row = succBoards[idx]->getRow();
		col = succBoards[idx]->getCol();
	}
	return minVal;
}

// Mostly the same as minValue, except finding the maxVal
int MinimaxPlayer::maxValue(int &row, int &col, OthelloBoard *board){
	vector<OthelloBoard*> succBoards;
	int maxVal = -1000000;

	// Check if the board is at a terminal state (no legal moves left)
	if((board->has_legal_moves_remaining('X') == false) && (board->has_legal_moves_remaining('O') == false)){
		return util(board);
	}

	// If not, find succBoards and continue recursively
	int newRow = 0;
	int newCol = 0;
	int val;
	int idx = 0;

	succBoards = succ('X', board);

	for(int i = 0; i < succBoards.size(); i++){
		val = minValue(row, col, succBoards[i]);
		if(val > maxVal){
			newRow = succBoards[i]->getRow();
			newCol = succBoards[i]->getCol();
			maxVal = val;
			idx = i;
		}
		row = succBoards[idx]->getRow();
		col = succBoards[idx]->getCol();
	}
	return maxVal;
}

void MinimaxPlayer::get_move(OthelloBoard* b, int& col, int& row) {
	if(symbol == 'X'){
		maxValue(row, col, b);
	}
	else if(symbol == 'O'){
		minValue(row, col, b);
	}
}

MinimaxPlayer* MinimaxPlayer::clone() {
	MinimaxPlayer* result = new MinimaxPlayer(symbol);
	return result;
}
