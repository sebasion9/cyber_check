#pragma once
#include<iostream>
#include<vector>
#include"Player.h"
typedef std::pair<Player*, Player*> player_pair;
class State {
public:

	static player_pair _players;
	static bool _turn;
	player_pair get_player();
	Player* get_player(bool id);
	static void turn();
	static bool whosturn();

};