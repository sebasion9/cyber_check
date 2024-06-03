#include"Game.h"
Game::Game(sf::VideoMode vm, const sf::String& title, std::string font_path) {

    _window = new sf::RenderWindow(vm, title, sf::Style::Resize | sf::Style::Fullscreen);
    _board = Board(*_window);
    _should_draw_legal_moves = false;
    _renderer = TextRenderer(_board.fields[0], _board.field_size * 8, font_path);
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

void Game::load_textures() {
    _textures = AssetLoader::load_textures();
}

void Game::reset() {

    for (size_t i = 0 ; i < 8; i++) {
        _board.pieces.push_back(
            std::make_pair(vec2u(i, 1), new Pawn(
                _textures["pawn"],
                _board.fields[1*8 + i],
                _board.field_size,
                BLACK_PIECE,
                STRAIGHT,
                vec2u(i, 1))));
        _board.pieces.push_back(
            std::make_pair(vec2u(i, 6), new Pawn(
                _textures["pawn"],
                _board.fields[6*8 + i],
                _board.field_size,
                WHITE_PIECE,
                STRAIGHT,
                vec2u(i, 6))));
    }
    _board.pieces.push_back(
        std::make_pair(vec2u(0, 0), new Rook(
            _textures["rook"],
            _board.fields[0],
            _board.field_size,
            BLACK_PIECE,
            STRAIGHT,
            vec2u(0, 0)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(7, 0), new Rook(
            _textures["rook"],
            _board.fields[7],
            _board.field_size,
            BLACK_PIECE,
            STRAIGHT,
            vec2u(7, 0)
        )));

    _board.pieces.push_back(
        std::make_pair(vec2u(7, 7), new Rook(
            _textures["rook"],
            _board.fields[7*8+7],
            _board.field_size,
            WHITE_PIECE,
            STRAIGHT,
            vec2u(7, 7)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(0, 7), new Rook(
            _textures["rook"],
            _board.fields[7*8],
            _board.field_size,
            WHITE_PIECE,
            STRAIGHT,
            vec2u(0, 7)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(1, 0), new Knight(
            _textures["horse"],
            _board.fields[1],
            _board.field_size,
            BLACK_PIECE,
            JUMPY,
            vec2u(1,0)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(6, 0), new Knight(
            _textures["horse"],
            _board.fields[6],
            _board.field_size,
            BLACK_PIECE,
            JUMPY,
            vec2u(6, 0)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(1, 7), new Knight(
            _textures["horse"],
            _board.fields[1+8*7],
            _board.field_size,
            WHITE_PIECE,
            JUMPY,
            vec2u(1, 7)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(6, 7), new Knight(
            _textures["horse"],
            _board.fields[6+7*8],
            _board.field_size,
            WHITE_PIECE,
            JUMPY,
            vec2u(6, 7)
        )));

    _board.pieces.push_back(
        std::make_pair(vec2u(3, 0), new Queen(
            _textures["queen"],
            _board.fields[3],
            _board.field_size,
            BLACK_PIECE,
            STRAIGHT | DIAGONAL,
            vec2u(3, 0)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(3, 7), new Queen(
            _textures["queen"],
            _board.fields[3 + 7 * 8],
            _board.field_size,
            WHITE_PIECE,
            STRAIGHT | DIAGONAL,
            vec2u(3, 7)
        )));

    _board.pieces.push_back(
        std::make_pair(vec2u(4, 0), new King(
            _textures["king"],
            _board.fields[4],
            _board.field_size,
            BLACK_PIECE,
            STRAIGHT | DIAGONAL,
            vec2u(4, 0)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(4, 7), new King(
            _textures["king"],
            _board.fields[4 + 7 * 8],
            _board.field_size,
            WHITE_PIECE,
            STRAIGHT | DIAGONAL,
            vec2u(4, 7)
        )));

    _board.pieces.push_back(
        std::make_pair(vec2u(2, 0), new Bishop(
            _textures["bishop"],
            _board.fields[2],
            _board.field_size,
            BLACK_PIECE,
            DIAGONAL,
            vec2u(2, 0)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(5, 0), new Bishop(
            _textures["bishop"],
            _board.fields[5],
            _board.field_size,
            BLACK_PIECE,
            DIAGONAL,
            vec2u(5, 0)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(2, 7), new Bishop(
            _textures["bishop"],
            _board.fields[2 + 8 * 7],
            _board.field_size,
            WHITE_PIECE,
            DIAGONAL,
            vec2u(2, 7)
        )));
    _board.pieces.push_back(
        std::make_pair(vec2u(5, 7), new Bishop(
            _textures["bishop"],
            _board.fields[5 + 7 * 8],
            _board.field_size,
            WHITE_PIECE,
            DIAGONAL,
            vec2u(5, 7)
        )));
    for (auto& piece : _board.pieces) {
        auto legal_moves = piece.second->find_legal_moves();
        auto corrected_legal_moves = _board.correct_legal_moves(legal_moves, piece.second);
        piece.second->set_legal_moves(corrected_legal_moves);
    }
}

void Game::run() {
    if (!_window) return;
    sf::Clock clock;
    bool is_holding = false;
    bool is_smth_selected = false;
    bool check_legal_moves = false;
    reset();
    
    int frame_count = 0;
    float frame_time = 0;

    while (_window->isOpen()) {
        sf::Event event;
        while (_window->pollEvent(event)) {
            switch (event.type) {

            case sf::Event::Closed:
                _window->close();
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
                        
                        bool player_color = State::whosturn();
                        auto hovered_piece = _board.get_piece_by_field(_board.get_hovered());
                        
                        if (hovered_piece && hovered_piece->get_color() == player_color) {
                            _board.set_selected(hovered_piece->get_field_pos());
                            is_smth_selected = true;
                        }
                        else {
                            _board.set_selected(vec2f(-1.0, -1.0));
                            is_smth_selected = false;
                        }
                        
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
        State::set_under_attack({});
        for (auto& piece : _board.pieces) {
            if (piece.second->is_king()) {
                continue;
            }
            auto legal_moves = piece.second->find_legal_moves();
            auto corrected_legal_moves = _board.correct_legal_moves(legal_moves, piece.second);
            auto special_legal_moves = piece.second->special_legal_moves(corrected_legal_moves, _board.pieces);
            piece.second->set_legal_moves(special_legal_moves);
            if (piece.second->get_color() != State::whosturn()) {
                State::append_ua_fields(piece.second->get_legal_moves());
            }
        }
        for (auto& piece : _board.pieces) {
            if (piece.second->is_king()) {
                auto legal_moves = piece.second->find_legal_moves();
                auto corrected_legal_moves = _board.correct_legal_moves(legal_moves, piece.second);
                auto special_legal_moves = piece.second->special_legal_moves(corrected_legal_moves, _board.pieces);
                piece.second->set_legal_moves(special_legal_moves);
            }
        }

        _should_draw_legal_moves = false;
        vec2f selected_field = _board.get_selected();
        Piece* selected_piece = _board.get_piece_by_field(selected_field);
        if (is_holding) {
            if (selected_piece) {
                
                sf::Vector2i mouse_pos = sf::Mouse::getPosition();
                float mouse_x = (float)mouse_pos.x;
                float mouse_y = (float)mouse_pos.y;
                selected_piece->set_act_pos_mouse(mouse_x, mouse_y);

                _should_draw_legal_moves = true;
                std::vector<vec2f> legal_fields;
                for (auto &legal_move : selected_piece->get_legal_moves()) {
                    legal_fields.push_back(_board.get_field_by_board_index(legal_move));
                }

                _board.set_current_legal_fields(legal_fields);
            }
        }

        float delta_time = clock.restart().asSeconds();

        frame_count++;
        frame_time += delta_time;

        if (frame_time > 0.15f) {
            _fps = frame_count / frame_time;
            frame_count = 0;
            frame_time = 0.0f;

     
        }

        update();
        render();


    }
}

void Game::update() {
    _board.update();
    _renderer.update_texts(_fps);
}



void Game::render() {
    _window->clear(sf::Color::Black);
    _board.draw(*_window);
    _renderer.draw(*_window);
    if (_should_draw_legal_moves) {
        _board.draw_legal_fields(*_window);
    }
    for (auto &piece : _board.pieces) {
        piece.second->draw(*_window);
    }
    _window->display();
}

