#pragma once
#include<SFML/Graphics.hpp>
#include"cdef.h"
#include"pieces/Piece.h"

class Board {
	vec2f _hovered_field;
	vec2f _selected_field;
	std::vector<vec2f> _current_legal_fields;
public:
	std::vector<std::pair<vec2u, Piece*>> pieces;
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
	std::vector<std::pair<vec2u, Piece*>>* get_pieces();

	void update();
	void draw_legal_fields(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

};