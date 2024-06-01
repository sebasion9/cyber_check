#include"State.h"

bool State::_turn = 1;
player_pair State::_players = std::make_pair<Player*, Player*>(new Player(0, "Czarne"), new Player(1, "Biale"));


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
