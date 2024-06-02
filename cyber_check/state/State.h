#pragma once
#include<iostream>
#include<vector>
#include"Player.h"
typedef std::pair<Player*, Player*> player_pair;
class State {
public:
	static int score;
	static int get_score();
	static void set_score(int _score);
	static player_pair _players;
	static bool _turn;
	static player_pair get_player();
	static Player* get_player(bool id);
	static void turn();
	static bool whosturn();
};