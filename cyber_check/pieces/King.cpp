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
std::vector<vec2u> King::special_legal_moves(std::vector<vec2u> legal_moves, std::vector<std::pair<vec2u, Piece*>> pieces) {
	auto board_idx = get_board_index();
	auto kingX = board_idx.x;
	auto kingY = board_idx.y;
	auto ua_fields = State::get_under_attack();
	bool turn = State::whosturn();
	for (auto& ua_field : ua_fields) {
		for (auto& legal_move : legal_moves) {
			if (ua_field.x == legal_move.x && ua_field.y == legal_move.y) {
				auto found = std::find(legal_moves.begin(), legal_moves.end(), ua_field);
				if (found != legal_moves.end()) {
					legal_moves.erase(found);
				}
			}
		}
		if (ua_field.x == kingX && ua_field.y == kingY && get_color() == turn) {
			std::cout << (get_color() ? "white " : "black ") << "king is checked!" << std::endl;
		}
		
	}
	return legal_moves;
}
bool King::is_king() {
	return true;
}

int King::get_value() {
	return 0;
}



