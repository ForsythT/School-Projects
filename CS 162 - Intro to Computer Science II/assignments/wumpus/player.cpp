#include "player.h"

Player::Player(){
	arrows = 3;
	num_moves = 0;
	gold = false;
	w_kill = false;
	alive = true;
}

void Player::set_alive(bool a){
	alive = a;
}

bool Player::get_alive(){
	return alive;
}

void Player::set_wumpus(bool w){
	w_kill = w;
}

bool Player::get_wumpus(){
	return w_kill;
}

int Player::get_arrows(){
	return arrows;
}

void Player::set_arrows(int a){
	arrows = a;
}

void Player::set_x(int xpos){
	x = xpos;
}

void Player::set_y(int ypos){
	y = ypos;
}

int Player::get_x(){
	return x;
}

int Player::get_y(){
	return y;
}

void Player::set_gold(bool g){
	gold = g;
}

bool Player::get_gold(){
	return gold;
}

void Player::set_num_moves(int n){
	num_moves = n;
}

int Player::get_num_moves(){
	return num_moves;
}

void Player::move_north(){
	y++;
}

void Player::move_south(){
	y--;
}

void Player::move_east(){
	x++;
}

void Player::move_west(){
	x--;
}
