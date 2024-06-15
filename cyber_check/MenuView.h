#pragma once
#include<SFML/Graphics.hpp>;
#include<iostream>
#include<regex>
#include"cdef.h"
#include"state/State.h"
#include"AssetLoader.h"
namespace MenuColors {
    const sf::Color BACKGROUND = sf::Color(6,8,28);
    const sf::Color PRIMARY = sf::Color(34, 40, 49);
    const sf::Color SECONDARY = sf::Color(2, 131, 145);
    const sf::Color TEXT_PRIMARY = sf::Color(200, 191, 184);
    const sf::Color TEXT_SECONDARY = sf::Color(238,238,238);
    const sf::Color TEXT_OK = sf::Color(141, 236, 180);
    const sf::Color TEXT_NOK = sf::Color(238, 78, 78);
    const sf::Color HOVER = sf::Color(
        PRIMARY.r * 0.65,
        PRIMARY.r * 0.65,
        PRIMARY.g * 0.65
    );
    const sf::Color SELECT = BACKGROUND;
}
namespace MainBtn {
    const int menu_rect = 0;
    const int play_btn = 1;
    const int opts_btn = 2;
    const int leaderboard_btn = 3;
    const int exit_btn = 4;
}
namespace MainText {
    const int game_title = 0;
    const int play_text = 1;
    const int opts_text = 2;
    const int leaderboard_text = 3;
    const int exit_text = 4;
}
namespace PlayBtn {
    const int t1 = 1;
    const int t2 = 2;
    const int t3 = 3;
    const int back = 4;
    const int second_box = 5;
    const int label1 = 6;
    const int input1 = 7;
    const int label2 = 8;
    const int input2 = 9;
    const int play = 10;
}
namespace PlayText {
    const int name1 = 5;
    const int name2 = 7;
}


class MenuView {
    sf::RenderWindow* _window;
    std::vector<sf::Drawable*> _drawables;
    std::vector<sf::Text*> _texts;
    std::vector<sf::Sprite*> _pieces;
public:
    int sel_idx;
    sf::Font font;
    MenuView();
    MenuView(sf::RenderWindow* win, const std::string &font_path);
    
    void clear_mem();
    void color_hover();
    void color_select(int selected);
    void clear_btns();
    void menu_box();

    void main_menu();
    int play_menu();
    void opts();
    void leaderboard();

    void init_text(const std::string& txt_str, sf::FloatRect rect);
    sf::FloatRect init_rect(int idx);
    sf::FloatRect init_rect(int idx, sf::FloatRect dest);
    void init_pieces();
    int loop();
    void update();
    void draw();
};
