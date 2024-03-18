#pragma once
#include<SFML/Graphics.hpp>
#include<unordered_map>
#include"Board.h"
#include"AssetLoader.h"
#include"cdef.h"
class Game {
    float _fps;
    State _state;
    Board _board;
    sf::RenderWindow* _window;
    std::unordered_map<std::string, sf::Texture*> _textures;
public:
    sf::Font font;
    Game(sf::VideoMode vm, const sf::String &title, std::string font_path);
    ~Game();
    void load_textures();
    void push_piece(const std::string& piece_name, uint32_t index, sf::Color color);
    void reset();
    bool mouse_in_board_bounds();
    void run();
    void render();
    void update();
};