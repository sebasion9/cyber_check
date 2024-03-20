#include"Piece.h"

std::vector<vec2u> Piece::find_legal_moves() {
	std::vector<vec2u> vec;
	return vec;
}



Piece::Piece(
	sf::Texture* texture,
	const vec2f& pos,
	uint32_t field_size,
	sf::Color color,
	vec2u board_index)

	: PieceView(texture,
		pos,
		field_size,
		color) {
	set_board_index(board_index);

};
