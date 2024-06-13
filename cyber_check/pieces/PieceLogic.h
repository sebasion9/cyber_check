#pragma once
#include"PieceView.h"
#include<vector>

enum MoveType {
	JUMPY = 1 << 0,
	DIAGONAL = 1 << 1,
	STRAIGHT = 1 << 2,
	PAWN = 1 << 3,
};

inline MoveType operator|(MoveType a, MoveType b)
{
	return static_cast<MoveType>(static_cast<int>(a) | static_cast<int>(b));
}

class PieceLogic {
	vec2u _board_index;
	bool _color;
	MoveType _mtype;
protected:
	std::vector<vec2u> _legal_moves;
	vec2u _calculate_board_index(vec2f field_pos, const std::vector<vec2f>& fields);
	int value;
public:
	virtual int get_value();
	bool get_color();
	void set_color(bool col);
	vec2u get_board_index();
	void set_board_index(vec2u pos);
	void set_board_index(uint32_t x, uint32_t y);

	MoveType get_mtype();
	void set_mtype(MoveType mtype);
	bool is_board_idx_in_vec2u(vec2u board_index, std::vector<vec2u> moves);
	

	virtual std::vector<vec2u> find_legal_moves() = 0;
	void set_legal_moves(const std::vector<vec2u> legal_moves);
	std::vector<vec2u> get_legal_moves();
};