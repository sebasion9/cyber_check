#pragma once
#include<SFML/Graphics.hpp>
#include<unordered_map>
#include"Board.h"
#include"TextRenderer.h"
#include"pieces/Rook.h"
#include"pieces/Bishop.h"
#include"pieces/Knight.h"
#include"pieces/King.h"
#include"pieces/Queen.h"
#include"pieces/Pawn.h"
#include"AssetLoader.h"
#include"state/State.h"
#include"MenuView.h"
#include"cdef.h"
#include<mutex>
#include<ranges>
enum class View {
    Menu,
    Match,
    Endgame
};

class Game {
    View _view;
    bool _should_draw_legal_moves;
    float _fps;
    Board _board;
    TextRenderer _renderer;
    sf::RenderWindow* _window;
    std::unordered_map<std::string, sf::Texture*> _textures;
    MenuView _menu_view;
public:
    sf::Font font;
    Game();
    Game(sf::RenderWindow* win, std::string font_path);
    ~Game();
    void load_textures();
    
    void reset();
    
    bool mouse_in_board_bounds();
    void run();
    
    void match();

    void render();
    void update();
};
