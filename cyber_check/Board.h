#pragma once
#include<SFML/Graphics.hpp>
#include"cdef.h"
#include"pieces/Piece.h"

class Board {
	vec2u _selected_field;
public:
	std::vector< Piece* > pieces;
	std::vector<vec2u> fields;
	uint32_t field_size;
	Board();
	Board(const sf::RenderWindow& window);
	vec2u get_selected();
	void set_selected(vec2u field);
	vec2u get_field_by_ccords(char letter, uint32_t num);
	vec2u get_field_by_mouse_cords(uint32_t x, uint32_t y);
	void draw(sf::RenderWindow& window);

};