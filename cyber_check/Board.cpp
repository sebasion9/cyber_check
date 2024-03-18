#include "Board.h"
Board::Board() {
    field_size = 0;
}

Board::Board(const sf::RenderWindow& window) {
    vec2u cords = window.getSize();
    float y_eight = ((float)cords.y / 10.0f);
    float inline_margin = ((float)cords.x - 8.0f * y_eight) / 2.0f;
    float horizontal_margin = ((float)cords.y - 8.0f * y_eight) / 2.0f;

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            uint32_t x = j * y_eight + inline_margin;
            uint32_t y = i * y_eight + horizontal_margin;
            fields.push_back(vec2f(x, y));
        }
    }
    field_size = y_eight;
    _hovered_field = fields[0];
}

vec2f Board::get_hovered() {
    return _hovered_field;
}

void Board::set_hovered(vec2f field) {
    
    _hovered_field = field;
}

vec2f Board::get_selected() {
    return _selected_field;
}

void Board::set_selected(vec2f field) {

    _selected_field = field;
}


vec2f Board::get_field_by_ccords(char letter, uint32_t num) {
    if (letter < 'a' || letter > 'h' || num > 8 || num < 1) {
        return fields[0];
    }
    size_t letter_num = (size_t)letter - 97;
    size_t cst_num = (size_t)num - 1;
    return fields[letter_num + cst_num * 8];

}

vec2f Board::get_field_by_mouse_cords(uint32_t x, uint32_t y) {
    for (auto &field : fields) {
        if ((x > field.x && x < field.x + field_size) && (y > field.y && y < field.y + field_size)) return field;
    }
    return _hovered_field;
}

Piece* Board::get_piece_by_field(vec2f field) {
    for (auto &piece : pieces) {
        vec2f piece_pos = piece->get_field_pos();
        if (field.x == piece_pos.x && field.y == piece_pos.y) {
            return piece;
        }
    }
    return nullptr;
}



void Board::update() {
    for (auto piece : pieces) {
        piece->update(field_size, fields);
    }
}

void Board::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < fields.size(); i++) {
        sf::RectangleShape rect(sf::Vector2f(field_size - 5, field_size - 5));
        sf::Color field_color = (i / 8 + i % 8) % 2 == 0 ? BLACK : WHITE;
        rect.setFillColor(field_color);

        rect.setPosition(fields[i].x, fields[i].y);
        window.draw(rect);
    }
    sf::RectangleShape hovered(sf::Vector2f(field_size - 5, field_size - 5));
    hovered.setPosition(_hovered_field.x, _hovered_field.y);
    hovered.setOutlineColor(sf::Color::Yellow);
    hovered.setOutlineThickness(5);
    hovered.setFillColor(sf::Color::Transparent);
    window.draw(hovered);
}
