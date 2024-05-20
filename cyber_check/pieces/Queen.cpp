#include"Queen.h"

std::vector<vec2u> Queen::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	int x = piece_pos.x;
	int y = piece_pos.y;
	int x_delta = piece_pos.x - piece_pos.y;
	std::vector<vec2u> vec;
	for(int i = 0; i < 8;i++) {
		for(int j = 0; j < 8; j++) {

			int y1 = i - x_delta;
			int y_delta = piece_pos.y - y1;
			int mirror_y = piece_pos.y + y_delta;
			if (mirror_y >= 0 && mirror_y < 8 && (i != x && mirror_y != y)) {
				vec.push_back(vec2u(i, mirror_y));
			}
			if (y1 >= 0 && y1 < 8 && (i != x && y1 != y)) {
				vec.push_back(vec2u(i, y1));
			}
			if ((i == x) != (j == y) ) {
				vec.push_back(vec2u(i, j));
			}
			
		}
	}
	

	return vec;
}




