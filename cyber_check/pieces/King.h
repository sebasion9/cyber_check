#pragma once
#include"Piece.h"

class King : public Piece {
	bool _checked;
public:
	using Piece::Piece;
	std::vector<vec2u> find_legal_moves();
	std::vector<vec2u> special_legal_moves(std::vector<vec2u> legal_moves, std::vector<Piece*> pieces);
	bool is_king();
	bool is_checked();
	int get_value();
};
