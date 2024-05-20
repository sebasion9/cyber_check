#include"Pawn.h"

std::vector<vec2u> Pawn::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	int x = piece_pos.x;
	int y = piece_pos.y;
	std::vector<vec2u> vec;
	
	// WHITE PAWN
	if (get_color()) {
		if (y == 6) {
			vec.push_back(vec2u(x, 5));
			vec.push_back(vec2u(x, 4));
			return vec;
		}
		if (y > 0) {
			vec.push_back(vec2u(x, y - 1));
		}
		return vec;
	}
	if (y == 1) {
		vec.push_back(vec2u(x, 2));
		vec.push_back(vec2u(x, 3));
		return vec;
	}
	if (y < 7) {
		vec.push_back(vec2u(x, y + 1));
	}

	return vec;
}
