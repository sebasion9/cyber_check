#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../cdef.h"
class Piece {
	sf::Sprite* _sprite;
	sf::Texture* _texture;
	vec2u _field_pos;
	vec2u _actual_pos;
	bool _is_moving;
	void _load_texture(const std::string &texture_path);
	vec2u _calculate_actual_pos(uint32_t field_size, const vec2u& pos);
	sf::IntRect _calculate_intrect(uint32_t field_size, const vec2u& act_pos);
	sf::Sprite* _create_sprite(const sf::IntRect& int_rect, sf::Color color);
public:
	void set_act_pos(uint32_t x, uint32_t y);
	void set_field_pos(uint32_t x, uint32_t y);
	Piece(
		const std::string &texture_path,
		const vec2u &pos, 
		uint32_t field_size, 
		sf::Color color);
	void draw(sf::RenderWindow &window);
};

