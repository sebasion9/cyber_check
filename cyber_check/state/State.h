#pragma once
#include<iostream>
#include"Player.h"
typedef std::pair<Player*, Player*> player_pair;
class State {

	player_pair _players;
	bool _turn;
public:
	player_pair get_player();
	Player* get_player(bool id);
	void turn();
	bool whosturn();

	State();
	~State();
};