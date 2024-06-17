#include"State.h"
int State::score = 0;
bool State::_turn = 1;
bool State::_draw = false;
player_pair State::_players = std::make_pair<Player*, Player*>(new Player(0, "Black"), new Player(1, "White"));
std::vector<vec2u> State::under_attack_fields = {};

std::vector<vec2u> State::get_under_attack() {
	return under_attack_fields;
}
void State::set_under_attack(std::vector<vec2u> ua_fields) {
	under_attack_fields = ua_fields;
}
void State::append_ua_fields(std::vector<vec2u> ua_fields) {
	for (auto& ua_field : ua_fields) {
		under_attack_fields.push_back(ua_field);
	}
}

player_pair State::get_player() {
	return _players;
}

Player* State::get_player(bool id) {
	if (id) return _players.first;
	return _players.second;
}

void State::turn() {
	_turn = !_turn;
}

bool State::whosturn() {
	return _turn;
}

int State::get_score() {
	return score;
}
void State::set_score(int _score) {
	score = _score;
}

void State::reset() {
	score = 0;
	_turn = 1;
	under_attack_fields = {};
	_draw = false;
}