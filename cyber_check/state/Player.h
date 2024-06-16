#pragma once
#include<iostream>
#include<string>
#include<thread>
#include<mutex>
class Player {
	bool _color;
	int _time;
	std::string _name;
public:
	static std::mutex time_mtx;
	static std::condition_variable cv;
	static bool turn;
	static bool end;
	bool get_color();
	void set_color(bool color);

	int get_time();
	std::string get_time_str();
	void set_time(int time);

	std::string get_name();
	void set_name(std::string name);
	void decrement_time();

	Player(bool color, std::string name);
};