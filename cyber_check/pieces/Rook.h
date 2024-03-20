#pragma once
#include"Piece.h"
class Rook : public Piece {
	std::vector<vec2u> _legal_moves;


public:

	Rook(sf::Texture* texture,
		const vec2f& pos,
		uint32_t field_size,
		sf::Color color,
		vec2u board_index);


	std::vector<vec2u> find_legal_moves();
	bool is_move_legal(vec2u dest);
};