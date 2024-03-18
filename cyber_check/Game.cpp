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

bool Game::mouse_in_board_bounds() {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition();
    if (_board.fields.size() < 64) {
        return false;
    }
    if (mouse_pos.x > _board.fields[0].x && (mouse_pos.x < _board.fields[7].x + _board.field_size)
        && mouse_pos.y > _board.fields[0].y && (mouse_pos.y < _board.fields[63].y + _board.field_size)) {
        return true;
    }
    return false;
}

void Game::run() {
    if (!_window) return;
    sf::Clock clock;
    bool is_holding = false;
    bool is_smth_selected = false;
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
                    vec2f field = _board.get_field_by_ccords('a', 3);
                }
                break;
            case sf::Event::MouseMoved:
                if (mouse_in_board_bounds()) {
                    vec2f field = _board.get_field_by_mouse_cords(event.mouseMove.x, event.mouseMove.y);
                    _board.set_hovered(field);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (mouse_in_board_bounds()) {
                    is_holding = true;
                    if (!is_smth_selected) {
                        _board.set_selected(_board.get_hovered());
                        is_smth_selected = true;
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (is_holding) {
                    is_holding = false;
                    is_smth_selected = false;
                }
                break;
            default:
                break;
            }

        }
        vec2f selected_field = _board.get_selected();
        Piece* selected_piece = _board.get_piece_by_field(selected_field);
        if (is_holding) {
            if (selected_piece) {
                sf::Vector2i mouse_pos = sf::Mouse::getPosition();
                float mouse_x = (float)mouse_pos.x;
                float mouse_y = (float)mouse_pos.y;
                selected_piece->set_act_pos_mouse(mouse_x, mouse_y);
                update();
            }
            
        }
        float current_time = clock.restart().asSeconds();
        float fps = 1.0f / current_time;

        update();
        render();
    }
}

void Game::update() {
    _board.update();
}

void Game::render() {
    _window->clear(sf::Color::Black);
    _board.draw(*_window);
    for (auto piece : _board.pieces) {
        piece->draw(*_window);
    }
    _window->display();
}

