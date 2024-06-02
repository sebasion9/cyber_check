#pragma once
#include"Piece.h"
class Rook : public Piece {
public:
	using Piece::Piece;
	std::vector<vec2u> find_legal_moves();
	int get_value();
};