#include"Player.h"
std::mutex Player::time_mtx;
std::condition_variable Player::cv;
bool Player::turn;

bool Player::get_color() {
	return _color; 
}

void Player::set_color(bool color) {
	_color = color;
}

int Player::get_time() {
	return _time;
}
std::string Player::get_time_str() {
	int seconds = _time / 1000;
	int minutes = seconds / 60;
	seconds = seconds - (minutes * 60);
	std::string min_str = std::to_string(minutes);
	std::string sec_str = std::to_string(seconds);
	while (min_str.size() < 2) min_str = '0' + min_str;
	while (sec_str.size() < 2) sec_str = '0' + sec_str;
	return (min_str + ":" + sec_str);
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
using namespace std::chrono_literals;
void Player::decrement_time() {
	bool color = _color;
	for (;;) {
		std::unique_lock<std::mutex> time_lock(time_mtx);
		cv.wait(time_lock, [color] {return color == turn;  });
		std::this_thread::sleep_for(1000ms);
		if (_time >= 1000) {
			set_time(_time - 1000);
		}
		else {
			break;
		}
		time_lock.unlock();
		cv.notify_one();
	}
}

Player::Player(bool color, std::string name) {
	set_name(name);
	set_color(color);
	set_time(599999);
}