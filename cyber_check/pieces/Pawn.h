#pragma once
#include"Piece.h"
class Pawn : public Piece {
public:
	using Piece::Piece;
	std::vector<vec2u> find_legal_moves();
	std::vector<vec2u> special_legal_moves(std::vector<vec2u> legal_moves, std::vector<Piece*> pieces, std::vector<vec2f> fields);
	int get_value();
};

