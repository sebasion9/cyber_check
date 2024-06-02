#pragma once
#include<iostream>
class Player {
	bool _color;
	int _time;
	std::string _name;
public:
	bool get_color();
	void set_color(bool color);

	int get_time();
	void set_time(int time);

	std::string get_name();
	void set_name(std::string name);

	Player(bool color, std::string name);
};