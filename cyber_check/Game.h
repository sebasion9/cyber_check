#pragma once
#include<SFML/Graphics.hpp>
#include"Board.h"
#include"cdef.h"
class Game {
    State _state;
    Board _board;
    sf::RenderWindow* _window;
public:
    sf::Font font;
    Game(sf::VideoMode vm, const sf::String& title, std::string font_path);
    ~Game();
    void run();
    void render();
    void update();
};