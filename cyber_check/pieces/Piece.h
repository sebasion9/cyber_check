#pragma once
#include<SFML/Graphics.hpp>
#include<iostream>
#include"../cdef.h"
class Piece {
	sf::Sprite* _sprite;
	sf::Texture* _texture;
	vec2f _field_pos;
	vec2f _actual_pos;
	vec2f _calculate_actual_pos(uint32_t field_size, const vec2f& pos);
	vec2f _find_field_pos_from_actual_center(uint32_t field_size, const std::vector<vec2f> &fields);
	bool _is_in_field_bounds_center(vec2f field, uint32_t field_size);
	sf::IntRect _calculate_intrect(uint32_t field_size, const vec2f& act_pos);
	sf::Sprite* _create_sprite(const sf::IntRect& int_rect, sf::Color color);
public:

	vec2f get_field_pos();
	vec2f get_actual_pos();
	void set_act_pos_mouse(float x, float y);
	void set_act_pos(float x, float y);
	void set_field_pos(float x, float y);
	Piece(
		const std::string &texture_path,
		const vec2f&pos,
		uint32_t field_size, 
		sf::Color color
	);

	Piece(
		sf::Texture* texture,
		const vec2f& pos,
		uint32_t field_size,
		sf::Color color
	);

	void update(uint32_t field_size, const std::vector<vec2f> &fields);
	void draw(sf::RenderWindow &window);
};

