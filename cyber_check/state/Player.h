#pragma once
class Player {
	int _score;
	bool _color;
public:
	bool get_color();
	void set_color(bool color);

	int get_score();
	void set_score(int score);

	Player(bool color);
};