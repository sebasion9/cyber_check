#include"Knight.h"

std::vector<vec2u> Knight::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	std::vector<vec2u> vec;
	
	int x = piece_pos.x + 2;
	int y1 = piece_pos.y + 1;
	int y2 = piece_pos.y - 1;

	int y = piece_pos.y + 2;
	int x1 = piece_pos.x + 1;
	int x2 = piece_pos.x - 1;

	if (x < 8) {
		if (y1 < 8) {
			vec.push_back(vec2u(x, y1));
		}
		if (y2 >= 0) {
			vec.push_back(vec2u(x, y2));
		}
	}
	x = piece_pos.x - 2;
	if (x >= 0) {
		if (y1 < 8) {
			vec.push_back(vec2u(x, y1));
		}
		if (y2 >= 0) {
			vec.push_back(vec2u(x, y2));
		}
	}

	if (y < 8) {
		if (x1 < 8) {
			vec.push_back(vec2u(x1, y));
		}
		if (x2 >= 0) {
			vec.push_back(vec2u(x2, y));
		}
	}
	y = piece_pos.y - 2;
	if (y >= 0) {
		if (x1 < 8) {
			vec.push_back(vec2u(x1, y));
		}
		if (x2 >= 0) {
			vec.push_back(vec2u(x2, y));
		}
	}

	return vec;
}




