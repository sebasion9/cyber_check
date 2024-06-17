#include"Piece.h"
//@returns 1 when piece moved otherwise 0
int Piece::update(uint32_t field_size, const std::vector<vec2f>& fields) {
	vec2u old_board_index = get_board_index();

	vec2f field = _find_field_pos_from_actual_center(field_size, fields);
	vec2f actual_pos = _calculate_actual_pos(field_size, field);
	vec2u board_index = _calculate_board_index(field, fields);


	if (is_board_idx_in_vec2u(board_index, get_legal_moves())) {
		set_board_index(board_index);
		set_field_pos(field.x, field.y);
		set_act_pos(actual_pos);
		if (old_board_index.x != board_index.x || old_board_index.y != board_index.y) {
			if (_castleable) {
				_castleable = !_castleable;
				int diff = board_index.x - old_board_index.x;
				if (is_king()) {
					if (diff > 1) {
						State::_castle = 1;
					}
					else if (diff < -1) {
						State::_castle = 2;
					}
				}
			}
			State::turn();
			return 1;
		}
		return 0;
	}

	vec2f old_act_pos = _calculate_actual_pos(field_size, get_field_pos());
	set_act_pos(old_act_pos);
	return 0;
}

std::vector<vec2u> Piece::find_legal_moves() {
	std::vector<vec2u> vec;
	return vec;
}
std::vector<vec2u> Piece::special_legal_moves(std::vector<vec2u> legal_moves, std::vector<Piece*> pieces, std::vector<vec2f> fields) {
	return legal_moves;
}
bool Piece::is_king() {
	return false;
}
bool Piece::is_checked() {
	return false;
}
bool Piece::castleable() {
	return _castleable;
}

Piece::Piece(
	sf::Texture* texture,
	const vec2f& pos,
	uint32_t field_size,
	sf::Color color,
	MoveType mtype,
	vec2u board_index)

	: PieceView(texture,
		pos,
		field_size,
		color) {
	set_board_index(board_index);
	color == WHITE_PIECE ? set_color(1) : set_color(0);
	set_legal_moves(find_legal_moves());
	set_mtype(mtype);
	_castleable = false;
};


Piece* Piece::get_piece_by_field(std::vector<Piece*> pieces, vec2f field) {
	for(auto const& piece : pieces) {
		vec2f piece_pos = piece->get_field_pos();
		if (field.x == piece_pos.x && field.y == piece_pos.y) {
			return piece;
		}
	}
	return nullptr;
}
vec2f Piece::get_field_by_board_index(vec2u board_index, std::vector<vec2f> fields) {
	uint32_t index = board_index.x + board_index.y * 8;
	return fields[index];
}