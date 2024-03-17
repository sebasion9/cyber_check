#include<iostream>
#include "Game.h"

int main()
{
    Game game(sf::VideoMode(1200, 800), "cyber check", "assets/712_serif.ttf");
    game.run();

    return 0;
}