#pragma once
#include"Piece.h"

class King : public Piece {
public:
	using Piece::Piece;
	std::vector<vec2u> find_legal_moves();
	std::vector<vec2u> special_legal_moves(std::vector<vec2u> legal_moves, std::vector<std::pair<vec2u, Piece*>> pieces);
	bool is_king();
	int get_value();
};
