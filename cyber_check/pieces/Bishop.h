#pragma once
#include"Piece.h"

class Bishop : public Piece {
public:
	using Piece::Piece;
	std::vector<vec2u> find_legal_moves();
};