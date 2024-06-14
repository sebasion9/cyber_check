#include<iostream>
#include<thread>
#include "Game.h"

int main()
{
    Audio audio;
    std::thread audio_thread(&Audio::play, &audio);

    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1200, 800), "cyber check", sf::Style::Resize | sf::Style::Fullscreen);
    Game game(window, "assets/712_serif.ttf");
    game.run();
    window->close();
    Audio::push_event(AudioEvent::Terminate);
    audio_thread.join();
    return 0;
}
