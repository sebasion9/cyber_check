#include"King.h"

std::vector<vec2u> King::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	std::vector<vec2u> vec;
	int x = piece_pos.x - 1;
	int y = piece_pos.y - 1;
	for(int i = x; i <= (x+2); i++) {
		for(int j = y; j <= (y+2); j++) {
			if(i < 0 || j < 0 || i > 7 || j > 7 || (i == (x+1) && j == (y+1))) {
				continue;
			}
			vec.push_back(vec2u(i, j));
		}
	}

	return vec;
}


int King::get_value() {
	return 0;
}



