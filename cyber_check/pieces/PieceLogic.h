#pragma once
#include"PieceView.h"
#include<vector>
class PieceLogic {
	vec2u _board_index;

public:
	vec2u get_board_index();
	void set_board_index(vec2u pos);
	void set_board_index(uint32_t x, uint32_t y);
	

	virtual std::vector<vec2u> find_legal_moves() = 0;
	virtual void on_drop() = 0;
};