#pragma once
#include"PieceView.h"
#include<vector>
class PieceLogic {
	vec2u _board_index;
protected:
	std::vector<vec2u> _legal_moves;
	vec2u _calculate_board_index(vec2f field_pos, const std::vector<vec2f>& fields);
public:
	vec2u get_board_index();
	void set_board_index(vec2u pos);
	void set_board_index(uint32_t x, uint32_t y);

	bool is_in_legal_moves(vec2u board_index);
	

	virtual std::vector<vec2u> find_legal_moves() = 0;
	void set_legal_moves(const std::vector<vec2u> legal_moves);
	std::vector<vec2u> get_legal_moves();
};