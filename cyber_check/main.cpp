#include<iostream>
#include<thread>
#include "Game.h"
int main()
{
    Audio audio;
    Game game(sf::VideoMode(1200, 800), "cyber check", "assets/712_serif.ttf");
    std::thread audio_thread(&Audio::play, &audio);

    game.run();
    audio_thread.join();


    return 0;
}
