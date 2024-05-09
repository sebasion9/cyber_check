#include "PieceView.h"


sf::IntRect PieceView::_calculate_intrect(uint32_t field_size, const vec2f &act_pos) {
	uint32_t new_size = field_size * 4 / 5;
	return sf::IntRect(act_pos.x, act_pos.y, new_size, new_size);
}

sf::Sprite* PieceView::_create_sprite(const sf::IntRect& int_rect, sf::Color color) {
	sf::Sprite* sprite = new sf::Sprite;
	vec2u text_size = _texture->getSize();
	float scaleX = int_rect.width / (float)text_size.x;
	float scaleY = int_rect.height / (float)text_size.y;
	sprite->setTexture(*_texture);
	sprite->setColor(color);
	sprite->setScale(scaleX, scaleY);
	return sprite;
}
vec2f PieceView::_calculate_actual_pos(uint32_t field_size, const vec2f& pos) {
	return vec2f(pos.x + field_size  / 10.0f - 2.0f, pos.y + field_size / 10.0f - 2.5f);
}

vec2f PieceView::_find_field_pos_from_actual_center(uint32_t field_size, const std::vector<vec2f> &fields) {
	for (auto &field : fields) {
		if (_is_in_field_bounds_center(field, field_size)) {
			return field;
		}
	}
	return _field_pos;
}

bool PieceView::_is_in_field_bounds_center(vec2f field, uint32_t field_size) {
	sf::FloatRect spr_bounds = _sprite->getGlobalBounds();
	float w = spr_bounds.width;
	float h = spr_bounds.height;

	if (   _actual_pos.x + w / 2.0f > field.x 
		&& _actual_pos.y + h / 2.0f > field.y
		&& _actual_pos.x + w / 2.0f < field.x + field_size
		&& _actual_pos.y + h / 2.0f < field.y + field_size) {
		return true;
	}
	return false;
}

vec2f PieceView::get_field_pos() {
	return _field_pos;
}

vec2f PieceView::get_actual_pos() {
	return _actual_pos;
}

void PieceView::set_act_pos_mouse(float x, float y) {
	sf::FloatRect spr_bounds = _sprite->getGlobalBounds();
	float w = spr_bounds.width;
	float h = spr_bounds.height;
	float actual_x = x - w/2.0f;
	float actual_y = y - h/2.0f;

	set_act_pos(actual_x, actual_y);

}

void PieceView::set_act_pos(float x, float y) {
	_actual_pos = vec2f(x, y);
	_sprite->setPosition(_actual_pos);
}

void PieceView::set_act_pos(vec2f pos) {
	_actual_pos = pos;
	_sprite->setPosition(pos);
}

void PieceView::set_field_pos(float x, float y) {
	_field_pos = vec2f(x, y);
}


PieceView::PieceView(
	sf::Texture* texture,
	const vec2f& pos,
	uint32_t field_size,
	sf::Color color) {
	_field_pos = pos;
	sf::IntRect int_rect = _calculate_intrect(field_size, _actual_pos);
	_texture = texture;
	_sprite = _create_sprite(int_rect, color);
	set_act_pos(_calculate_actual_pos(field_size, pos));
}


void PieceView::draw(sf::RenderWindow &window) {
	window.draw(*_sprite);
}
