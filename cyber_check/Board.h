#pragma once
#include<SFML/Graphics.hpp>
#include"cdef.h"
#include"pieces/Piece.h"

class Board {
	vec2f _hovered_field;
	vec2f _selected_field;
public:
	std::vector< Piece* > pieces;
	std::vector<vec2f> fields;
	uint32_t field_size;
	Board();
	Board(const sf::RenderWindow& window);
	
	// field methods

	vec2f get_hovered();
	vec2f get_selected();

	void set_hovered(vec2f field);
	void set_selected(vec2f field);

	vec2f get_field_by_ccords(char letter, uint32_t num);
	vec2f get_field_by_mouse_cords(uint32_t x, uint32_t y);

	// piece methods
	Piece* get_piece_by_field(vec2f field);

	void update();
	void draw(sf::RenderWindow& window);

};