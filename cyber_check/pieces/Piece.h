#pragma once
#include"PieceLogic.h"
#include"PieceView.h"
class Piece : public PieceLogic, public PieceView {
public:
	void on_drop() {};
	virtual std::vector<vec2u> find_legal_moves();


	Piece(
		sf::Texture* texture,
		const vec2f& pos,
		uint32_t field_size,
		sf::Color color,
		vec2u board_index
	);

	~Piece();
};