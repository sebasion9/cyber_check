#include"Rook.h"

std::vector<vec2u> Rook::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	std::vector<vec2u> vec;
	for (size_t x = 0; x < 8; x++) {
		for (size_t y = 0; y < 8; y++) {
			if ((x == piece_pos.x) != (y == piece_pos.y)) {
				vec.push_back(vec2u(x, y));
			}
		}
	}
	return vec;
}

