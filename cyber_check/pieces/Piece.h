#pragma once
#include"PieceLogic.h"
#include"PieceView.h"
#include"../state/State.h"
#include"../Audio.h"
class Piece : public PieceLogic, public PieceView {
	
public:
	bool _castleable;
	int update(uint32_t field_size, const std::vector<vec2f>& fields);
	virtual std::vector<vec2u> find_legal_moves();
	virtual std::vector<vec2u> special_legal_moves(std::vector<vec2u> legal_moves, std::vector<Piece*> pieces, std::vector<vec2f> fields);
	virtual bool is_king();
	virtual bool is_checked();
	virtual bool castleable();

	static vec2f get_field_by_board_index(vec2u board_index, std::vector<vec2f> fields);
	static Piece* get_piece_by_field(std::vector<Piece*> pieces, vec2f field);
	explicit Piece(
		sf::Texture* texture,
		const vec2f& pos,
		uint32_t field_size,
		sf::Color color,
		MoveType mtype,
		vec2u board_index
	);

};