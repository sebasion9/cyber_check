#pragma once
#include<iostream>
#include<vector>
#include"Player.h"
#include"../cdef.h"
typedef std::pair<Player*, Player*> player_pair;
class State {
public:
	static std::vector<vec2u> under_attack_fields;
	static std::vector<vec2u> get_under_attack();
	static void set_under_attack(std::vector<vec2u> ua_fields);
	static void append_ua_fields(std::vector<vec2u> ua_fields);
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