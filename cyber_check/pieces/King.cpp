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
std::vector<vec2u> King::special_legal_moves(std::vector<vec2u> legal_moves, std::vector<Piece*> pieces, std::vector<vec2f> fields) {
	auto board_idx = get_board_index();
	auto kingX = board_idx.x;
	auto kingY = board_idx.y;
	auto color = get_color();
	auto ua_fields = State::get_under_attack();
	bool turn = State::whosturn();
	_checked = false;
	for (auto& ua_field : ua_fields) {
		for (auto& legal_move : legal_moves) {
			if (ua_field.x == legal_move.x && ua_field.y == legal_move.y) {
				auto found = std::find(legal_moves.begin(), legal_moves.end(), ua_field);
				if (found != legal_moves.end()) {
					legal_moves.erase(found);
				}
			}
		}
		_checked = _checked || (ua_field.x == kingX && ua_field.y == kingY && color == turn);
	}
	// white
	//R : 7,7 N: 6,7 N: 5,7
	//R : 0,7 N: 1,7 N: 2,7 N: 3,7
	// 
	// black
	//R : 0,0 N: 1,0 N: 2,0 N: 3,0
	//R : 7,0 N: 6,0 N: 5,0



	if (turn) {
		auto r1 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(7,7), fields));
		if (r1 != nullptr && r1->castleable()) {
			auto n1 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(6, 7), fields));
			auto n2 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(5, 7), fields));
			if (!n1 && !n2) {
				legal_moves.push_back(vec2u(6,7));
			}
		}
		auto r2 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(0, 7), fields));
		if (r2 != nullptr && r2->castleable()) {
			auto n1 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(1, 7), fields));
			auto n2 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(2, 7), fields));
			auto n3 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(3, 7), fields));
			if (!n1 && !n2 && !n3) {
				legal_moves.push_back(vec2u(2,7));
			}
		}
	}
	else {
		auto r1 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(7, 0), fields));
		if (r1 != nullptr && r1->castleable()) {
			auto n1 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(6, 0), fields));
			auto n2 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(5, 0), fields));
			if (!n1 && !n2) {
				legal_moves.push_back(vec2u(6,0));
			}
		}
		auto r2 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(0, 0), fields));
		if (r2 != nullptr && r2->castleable()) {
			auto n1 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(1, 0), fields));
			auto n2 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(2, 0), fields));
			auto n3 = Piece::get_piece_by_field(pieces, Piece::get_field_by_board_index(vec2u(3, 0), fields));
			if (!n1 && !n2 && !n3) {
				legal_moves.push_back(vec2u(2,0));
			}
		}
	}
	
	return legal_moves;
}
bool King::is_king() {
	return true;
}
bool King::is_checked() {
	return _checked;
}

int King::get_value() {
	return 0;
}



