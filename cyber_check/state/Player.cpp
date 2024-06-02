#include"Player.h"

bool Player::get_color() {
	return _color; 
}

void Player::set_color(bool color) {
	_color = color;
}

int Player::get_time() {
	return _time;
}

void Player::set_time(int time) {
	_time = time;
}
std::string Player::get_name() {
	return _name;
}
void Player::set_name(std::string name) {
	_name = name;
}

Player::Player(bool color, std::string name) {
	set_name(name);
	set_color(color);
	// dev value, before time formatting
	set_time(1000);
}