#pragma once
#include<SFML/Graphics.hpp>
#include<unordered_map>
#include"Board.h"
#include"pieces/Rook.h"
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
    
    void push_piece(uint32_t x, uint32_t y, sf::Color color, PieceType pt);
    void reset();
    
    bool mouse_in_board_bounds();
    void run();
    
    void render();
    void update();
};