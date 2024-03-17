#include "Piece.h"
void Piece::_load_texture(const std::string &texture_path) {
	sf::Texture* texture = new sf::Texture;
	if (!texture->loadFromFile(texture_path)) {
		std::cerr << "couldn't load texture from file (PIECE), exiting now" << std::endl;
		exit(1);
	}
	this->_texture = texture;
}

sf::IntRect Piece::_calculate_intrect(uint32_t field_size, const vec2u &act_pos) {
	uint32_t new_size = field_size * 4 / 5;
	return sf::IntRect(act_pos.x, act_pos.y, new_size, new_size);
}

sf::Sprite* Piece::_create_sprite(const sf::IntRect& int_rect, sf::Color color) {
	sf::Sprite* sprite = new sf::Sprite;
	vec2u text_size = _texture->getSize();
	float scaleX = int_rect.width / (float)text_size.x;
	float scaleY = int_rect.height / (float)text_size.y;
	sprite->setTexture(*_texture);
	sprite->setColor(color);
	sprite->setScale(scaleX, scaleY);
	return sprite;
}
vec2u Piece::_calculate_actual_pos(uint32_t field_size, const vec2u& pos) {
	return vec2u(pos.x + field_size * 1 / 10 - 2, pos.y + field_size * 1 / 10 - 2);
}

void Piece::set_act_pos(uint32_t x, uint32_t y) {
	_actual_pos = vec2u(x, y);
}

void Piece::set_field_pos(uint32_t x, uint32_t y) {
	_field_pos = vec2u(x, y);
}


Piece::Piece(
	const std::string& texture_path, 
	const vec2u& pos, 
	uint32_t field_size, 
	sf::Color color) {
	_is_moving = false;
	_field_pos = pos;
	_actual_pos = _calculate_actual_pos(field_size, pos);
	sf::IntRect int_rect = _calculate_intrect(field_size, _actual_pos);
	_load_texture(texture_path);
	_sprite = _create_sprite(int_rect, color);
	_sprite->setPosition(_actual_pos.x, _actual_pos.y);
}


void Piece::draw(sf::RenderWindow &window) {
	window.draw(*_sprite);
}