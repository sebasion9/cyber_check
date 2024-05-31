#pragma once
#include<SFML/Graphics.hpp>
#include<unordered_map>
#include"Board.h"
#include"pieces/Rook.h"
#include"pieces/Bishop.h"
#include"pieces/Knight.h"
#include"pieces/King.h"
#include"pieces/Queen.h"
#include"pieces/Pawn.h"
#include"AssetLoader.h"
#include"state/State.h"
#include"cdef.h"
class Game {
    bool _should_draw_legal_moves;
    float _fps;
    Board _board;
    sf::RenderWindow* _window;
    std::unordered_map<std::string, sf::Texture*> _textures;
public:
    sf::Font font;
    Game(sf::VideoMode vm, const sf::String &title, std::string font_path);
    ~Game();
    void load_textures();
    
    void reset();
    
    bool mouse_in_board_bounds();
    void run();
    
    void render();
    void update();
};
