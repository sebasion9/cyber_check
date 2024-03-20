#include"PieceLogic.h"

vec2u PieceLogic::get_board_index() {
	return _board_index;
}

void PieceLogic::set_board_index(vec2u pos) {
	_board_index = pos;
}

void PieceLogic::set_board_index(uint32_t x, uint32_t y) {
	_board_index = vec2u(x, y);
}

