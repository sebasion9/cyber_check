#include"Player.h"

bool Player::get_color() {
	return _color; 
}

void Player::set_color(bool color) {
	_color = color;
}

int Player::get_score() {
	return _score;
}

void Player::set_score(int score) {
	_score = score;
}

Player::Player(bool color) {
	set_score(0);
	set_color(color);
}