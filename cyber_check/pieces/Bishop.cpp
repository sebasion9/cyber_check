#include"Bishop.h"

std::vector<vec2u> Bishop::find_legal_moves() {
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
	return vec;
}




