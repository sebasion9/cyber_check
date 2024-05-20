#include"State.h"

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

State::State() {
	_players.first = new Player(0);
	_players.first = new Player(1);
	_turn = 0;
}

State::~State() {
	delete _players.first;
	delete _players.second;
}