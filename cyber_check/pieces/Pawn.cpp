#include"Pawn.h"

std::vector<vec2u> Pawn::find_legal_moves() {
	vec2u piece_pos = this->get_board_index();
	int x = piece_pos.x;
	int y = piece_pos.y;
	bool color = get_color();
	bool turn = State::whosturn();
	std::vector<vec2u> vec;
	
	// WHITE PAWN
	if (color) {
		if (color == !turn) {
			if (y > 0) {
				if (x > 0) vec.push_back(vec2u(x - 1, y - 1));
				if (x < 7) vec.push_back(vec2u(x + 1, y - 1));
				return vec;
			}
		}
		
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
	if (color == !turn) {
		if (y < 7) {
			if (x > 0) vec.push_back(vec2u(x - 1, y + 1));
			if (x < 7) vec.push_back(vec2u(x + 1, y + 1));
			return vec;
		}
	}

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
std::vector<vec2u> Pawn::special_legal_moves(std::vector<vec2u> legal_moves, std::vector<Piece*> pieces) {
	auto board_idx = get_board_index();
	auto pawnX = board_idx.x;
	auto pawnY = board_idx.y;
	bool color = get_color();
	bool turn = State::whosturn();
	if (color == !turn) {
		return legal_moves;
	}
	if (color) {
		for (auto& piece : pieces) {
			auto pieceXY = piece->get_board_index();
			if (pieceXY.y == pawnY - 1 && (pieceXY.x == pawnX - 1 || pieceXY.x == pawnX + 1)
				&& piece->get_color() != color) {
				legal_moves.push_back(pieceXY);
			}
			if (pieceXY.y == pawnY - 1 && pieceXY.x == pawnX) {
				auto found = std::find(legal_moves.begin(), legal_moves.end(), pieceXY);
				if (found != legal_moves.end()) {
					legal_moves.erase(found);
				}
			}
			if (pawnY == 6) {
				if (pieceXY.x == pawnX && pieceXY.y == pawnY - 1) {
					auto found = std::find(legal_moves.begin(), legal_moves.end(), vec2u(pawnX, 4));
					if (found != legal_moves.end()) {
						legal_moves.erase(found);
					}
				}
			}
		}
		return legal_moves;
	}
	for (auto& piece : pieces) {
		auto pieceXY = piece->get_board_index();
		if (pieceXY.y == pawnY + 1 && (pieceXY.x == pawnX - 1 || pieceXY.x == pawnX + 1)
			&& piece->get_color() != color) {
			legal_moves.push_back(pieceXY);
		}
		if (pieceXY.y == pawnY + 1 && pieceXY.x == pawnX) {
			auto found = std::find(legal_moves.begin(), legal_moves.end(), pieceXY);
			if (found != legal_moves.end()) {
				legal_moves.erase(found);
			}
		}
		if (pawnY == 1) {
			if (pieceXY.x == pawnX && pieceXY.y == pawnY + 1) {
				auto found = std::find(legal_moves.begin(), legal_moves.end(), vec2u(pawnX, 3));
				if (found != legal_moves.end()) {
					legal_moves.erase(found);
				}
			}
		}
	}
	return legal_moves;
}



int Pawn::get_value() {
	return 1;
}