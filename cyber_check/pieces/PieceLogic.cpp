#include"PieceLogic.h"

vec2u PieceLogic::_calculate_board_index(vec2f field_pos, const std::vector<vec2f> &fields) {
	uint32_t x, y;
	for (size_t i = 0; i < fields.size(); i++) {
		if (fields[i] == field_pos) {
			x = i / 8;
			y = i % 8;
			return vec2u(y, x);
		}
	}
	return get_board_index();
}

bool PieceLogic::is_in_legal_moves(vec2u board_index) {
	bool res = false;
	for (auto& move : _legal_moves) {
		res = (move.x == board_index.x && move.y == board_index.y);
		if (res) return res;
	}
	return res;
}
int PieceLogic::get_value() {
	return value;
}
bool PieceLogic::get_color() {
	return _color;
}
void PieceLogic::set_color(bool color) {
	this->_color = color;
}


void PieceLogic::set_legal_moves(const std::vector<vec2u> legal_moves) {
	_legal_moves = legal_moves;
}

std::vector<vec2u> PieceLogic::get_legal_moves() {
	return _legal_moves;
}

vec2u PieceLogic::get_board_index() {
	return _board_index;
}


void PieceLogic::set_board_index(vec2u pos) {
	_board_index = pos;
}

void PieceLogic::set_board_index(uint32_t x, uint32_t y) {
	_board_index = vec2u(x, y);
}



MoveType PieceLogic::get_mtype() {
	return _mtype;
}
void PieceLogic::set_mtype(MoveType mtype) {
	_mtype = mtype;
}