#pragma once
#include"PieceLogic.h"
#include"PieceView.h"
#include"../state/State.h"
class Piece : public PieceLogic, public PieceView {
	
public:
	int update(uint32_t field_size, const std::vector<vec2f>& fields);
	virtual std::vector<vec2u> find_legal_moves();
	virtual std::vector<vec2u> special_legal_moves(std::vector<vec2u> legal_moves, std::vector<std::pair<vec2u, Piece*>> pieces);
	virtual bool is_king();
	explicit Piece(
		sf::Texture* texture,
		const vec2f& pos,
		uint32_t field_size,
		sf::Color color,
		MoveType mtype,
		vec2u board_index
	);

	~Piece();
};