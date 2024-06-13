#pragma once
#include<SFML/Graphics.hpp>
#include"Audio.h"
#include"cdef.h"
#include"pieces/Piece.h"
class Board {
	vec2f _hovered_field;
	vec2f _selected_field;
	std::vector<vec2f> _current_legal_fields;
public:
	std::vector<Piece*> pieces;
	std::vector<vec2f> fields;
	uint32_t field_size;
	Board();
	Board(const sf::RenderWindow& window);
	
	// field methods

	vec2f get_hovered();
	vec2f get_selected();

	void set_hovered(vec2f field);
	void set_selected(vec2f field);
	void set_current_legal_fields(const std::vector<vec2f>& fields);

	vec2f get_field_by_mouse_cords(uint32_t x, uint32_t y);
	vec2f get_field_by_board_index(vec2u board_index);
	// piece methods
	Piece* get_piece_by_field(vec2f field);
	Piece* get_king_by_color(bool color);
	std::vector<Piece*>* get_pieces();
	std::vector<std::vector<vec2u>> sort_lm_by_selected_piece(const std::vector<vec2u>& legal_moves, Piece* selected_piece);
	std::vector<vec2u> correct_legal_moves(const std::vector<vec2u> &legal_moves, Piece* selected_piece);
	std::vector<int> get_pieceidx_by_boardidx(vec2u board_idx);

	std::vector<vec2u> calc_saveable_fields();
	std::vector<vec2u> intersect(std::vector<vec2u> fields1, std::vector<vec2u> fields2);

	void update();
	void draw_legal_fields(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

};