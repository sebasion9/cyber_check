#include"Piece.h"

void Piece::update(uint32_t field_size, const std::vector<vec2f>& fields) {
	vec2f field = _find_field_pos_from_actual_center(field_size, fields);
	vec2f actual_pos = _calculate_actual_pos(field_size, field);
	vec2u board_index = _calculate_board_index(field, fields);

	if (is_in_legal_moves(board_index)) {
		set_board_index(board_index);
		set_field_pos(field.x, field.y);
		set_act_pos(actual_pos);
		return;
	}
	
	vec2f old_act_pos = _calculate_actual_pos(field_size, get_field_pos());
	set_act_pos(old_act_pos);
	
}

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
	color == WHITE_PIECE ? set_color(1) : set_color(0);
};


