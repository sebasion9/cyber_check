#pragma once
#include"PieceLogic.h"
#include"PieceView.h"
class Piece : public PieceLogic, public PieceView {

public:
	void update(uint32_t field_size, const std::vector<vec2f>& fields);
	virtual std::vector<vec2u> find_legal_moves();
	
	explicit Piece(
		sf::Texture* texture,
		const vec2f& pos,
		uint32_t field_size,
		sf::Color color,
		vec2u board_index
	);

	~Piece();
};