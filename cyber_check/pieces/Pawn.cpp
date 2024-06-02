#include"Pawn.h"

std::vector<vec2u> Pawn::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	int x = piece_pos.x;
	int y = piece_pos.y;
	std::vector<vec2u> vec;
	
	// WHITE PAWN
	if (get_color()) {
		if (y == 6) {
			vec.push_back(vec2u(x, 4));
			vec.push_back(vec2u(x, 5));
			return vec;
		}
		if (y > 0) {
			vec.push_back(vec2u(x, y - 1));
		}
		return vec;
	}
	// BLACK PAWN
	if (y == 1) {
		vec.push_back(vec2u(x, 2));
		vec.push_back(vec2u(x, 3));
		return vec;
	}
	if (y < 7) {
		vec.push_back(vec2u(x, y + 1));
	}

	return vec;
}
std::vector<vec2u> Pawn::special_legal_moves(std::vector<vec2u> legal_moves, std::vector<std::pair<vec2u, Piece*>> pieces) {
	auto board_idx = get_board_index();
	auto pawnX = board_idx.x;
	auto pawnY = board_idx.y;
	if (get_color()) {
		for (auto& piece : pieces) {
			auto pieceXY = piece.second->get_board_index();
			if (pieceXY.y == pawnY - 1 && (pieceXY.x == pawnX - 1 || pieceXY.x == pawnX + 1)
				&& piece.second->get_color() != get_color()) {
				legal_moves.push_back(pieceXY);
			}
			if (pieceXY.y == pawnY - 1 && pieceXY.x == pawnX) {
				auto found = std::find(legal_moves.begin(), legal_moves.end(), pieceXY);
				if (found != legal_moves.end()) {
					legal_moves.erase(found);
				}
			}
		}
		return legal_moves;
	}
	for (auto& piece : pieces) {
		auto pieceXY = piece.second->get_board_index();
		if (pieceXY.y == pawnY + 1 && (pieceXY.x == pawnX - 1 || pieceXY.x == pawnX + 1)
			&& piece.second->get_color() != get_color()) {
			legal_moves.push_back(pieceXY);
		}
		if (pieceXY.y == pawnY + 1 && pieceXY.x == pawnX) {
			auto found = std::find(legal_moves.begin(), legal_moves.end(), pieceXY);
			if (found != legal_moves.end()) {
				legal_moves.erase(found);
			}
		}
	}
	return legal_moves;
}



int Pawn::get_value() {
	return 1;
}