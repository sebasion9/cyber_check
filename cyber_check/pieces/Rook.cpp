#include"Rook.h"



Rook::Rook(sf::Texture* texture,
	const vec2f& pos,
	uint32_t field_size,
	sf::Color color,
	vec2u board_index) 

: Piece(texture,
		pos,
		field_size,
		color,
		board_index) {};


std::vector<vec2u> Rook::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	std::vector<vec2u> vec;
	std::cout << "legal moves: \n";
	for (size_t x = 0; x < 8; x++) {
		for (size_t y = 0; y < 8; y++) {
			if (x == piece_pos.x || y == piece_pos.y) {
				vec.push_back(vec2u(x, y));
				std::cout << "x: " << x << ", y: " << y << "\n";
			}
		}
	}
	std::cout << "--- \n";
	return vec;
}

bool Rook::is_move_legal(vec2u dest) {
	return 0;
}