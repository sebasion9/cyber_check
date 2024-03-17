#include"Game.h"

Game::Game(sf::VideoMode vm, const sf::String& title, std::string font_path) {
    if (!font.loadFromFile(font_path)) {
        std::cerr << "couldnt load font, exiting now";
        exit(1);
    }
    _window = new sf::RenderWindow(vm, title, sf::Style::Resize | sf::Style::Fullscreen);
    _board = Board(*_window);
    _state = State::MENU;
}
Game::~Game() {
    delete _window;
}

void Game::run() {
    if (!_window) return;
    sf::Clock clock;
    float last_time = 0;

    // test piece 
    _board.pieces.push_back(new Piece("assets/rook.png", _board.fields[0], _board.field_size, WHITE_PIECE));
    _board.pieces.push_back(new Piece("assets/bishop.png", _board.fields[1], _board.field_size, WHITE_PIECE));
    _board.pieces.push_back(new Piece("assets/rook.png", _board.fields[2], _board.field_size, BLACK_PIECE));
    _board.pieces.push_back(new Piece("assets/bishop.png", _board.fields[3], _board.field_size, BLACK_PIECE));
    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            switch (event.type) {

            case sf::Event::Closed:
                _window->close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.scancode == sf::Keyboard::Scan::Space) {
                    vec2u field = _board.get_field_by_ccords('a', 3);
                }
                break;
            case sf::Event::MouseMoved:
                if (true) {
                    vec2u field = _board.get_field_by_mouse_cords(event.mouseMove.x, event.mouseMove.y);
                    _board.set_selected(field);
                }
                break;
            default:
                break;
            }

        }
        float current_time = clock.restart().asSeconds();
        float fps = 1.0f / current_time;

        //update();
        render();
    }
}

void Game::render() {
    _window->clear(sf::Color::Black);
    _board.draw(*_window);
    for (auto piece : _board.pieces) {
        piece->draw(*_window);
    }
    _window->display();
}
