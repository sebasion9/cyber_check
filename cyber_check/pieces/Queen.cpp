#include"Queen.h"

std::vector<vec2u> Queen::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	std::vector<vec2u> vec;
	int x_delta = piece_pos.x - piece_pos.y;
	for (size_t i = 0; i < 8; i++) {

		int y = i - x_delta;
		int y_delta = piece_pos.y - y;
		int mirror_y = piece_pos.y + y_delta;
		if (piece_pos.x == i || piece_pos.y == y || piece_pos.y == mirror_y) {
			continue;
		}
		if (mirror_y >= 0 && mirror_y < 8) {
			vec.push_back(vec2u(i, mirror_y));
		}
		if (y >= 0 && y < 8) {
			vec.push_back(vec2u(i, y));
		}

	}
	for (size_t x = 0; x < 8; x++) {
		for (size_t y = 0; y < 8; y++) {
			if ((x == piece_pos.x) != (y == piece_pos.y)) {
				vec.push_back(vec2u(x, y));
			}
		}
	}
	return vec;
}

int Queen::get_value() {
	return 9;
}


