#include "Board.h"
Board::Board() {
    field_size = 0;
}

Board::Board(const sf::RenderWindow& window) {
    vec2u cords = window.getSize();
    uint32_t y_eight = (cords.y / 10);
    uint32_t inline_margin = (cords.x - 8 * y_eight) / 2;
    uint32_t horizontal_margin = (cords.y - 8 * y_eight) / 2;

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            uint32_t x = j * y_eight + inline_margin;
            uint32_t y = i * y_eight + horizontal_margin;
            fields.push_back(vec2u(x, y));
        }
    }
    field_size = y_eight;
    _selected_field = fields[0];
}

vec2u Board::get_selected() {
    return _selected_field;
}

void Board::set_selected(vec2u field) {
    
    _selected_field = field;
}
vec2u Board::get_field_by_ccords(char letter, uint32_t num) {
    if (letter < 'a' || letter > 'h' || num > 8 || num < 1) {
        return fields[0];
    }
    size_t letter_num = (size_t)letter - 97;
    size_t cst_num = (size_t)num - 1;
    return fields[letter_num + cst_num * 8];

}

vec2u Board::get_field_by_mouse_cords(uint32_t x, uint32_t y) {
    for (auto field : fields) {
        if ((x > field.x && x < field.x + field_size) && (y > field.y && y < field.y + field_size)) return field;
    }
    return _selected_field;
}


void Board::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < fields.size(); i++) {
        sf::RectangleShape rect(sf::Vector2f(field_size - 5, field_size - 5));
        sf::Color field_color = (i / 8 + i % 8) % 2 == 0 ? BLACK : WHITE;
        rect.setFillColor(field_color);

        rect.setPosition(fields[i].x, fields[i].y);
        window.draw(rect);
    }
    sf::RectangleShape selected(sf::Vector2f(field_size - 5, field_size - 5));
    selected.setPosition(_selected_field.x, _selected_field.y);
    selected.setOutlineColor(sf::Color::Yellow);
    selected.setOutlineThickness(5);
    selected.setFillColor(sf::Color::Transparent);
    window.draw(selected);
}
