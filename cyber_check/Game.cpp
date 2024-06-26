#include"Game.h"
Game::Game(sf::RenderWindow* win, std::string font_path) {
    _view = View::Menu;
    _window = win;
    _board = Board(*_window);
    _should_draw_legal_moves = false;
    _renderer = TextRenderer(_board.fields[0], _board.field_size * 8, font_path);
    _menu_view = MenuView(win, font_path);
}
Game::~Game() {
    delete _window;
}

bool Game::mouse_in_board_bounds() {
    sf::Vector2i mouse_pos = sf::Mouse::getPosition(*_window);
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
    if (!_board.pieces.empty()) {
        _board.pieces.clear();
    }
    State::reset();
    for (size_t i = 0 ; i < 8; i++) {
        _board.pieces.push_back(
            new Pawn(
                _textures["pawn"],
                _board.fields[1*8 + i],
                _board.field_size,
                BLACK_PIECE,
                PAWN,
                vec2u(i, 1)));
        _board.pieces.push_back(
            new Pawn(
                _textures["pawn"],
                _board.fields[6*8 + i],
                _board.field_size,
                WHITE_PIECE,
                PAWN,
                vec2u(i, 6)));
    }
    _board.pieces.push_back(
        new Rook(
            _textures["rook"],
            _board.fields[0],
            _board.field_size,
            BLACK_PIECE,
            STRAIGHT,
            vec2u(0, 0)
        ));
    _board.pieces.push_back(
        new Rook(
            _textures["rook"],
            _board.fields[7],
            _board.field_size,
            BLACK_PIECE,
            STRAIGHT,
            vec2u(7, 0)
        ));

    _board.pieces.push_back(
        new Rook(
            _textures["rook"],
            _board.fields[7*8+7],
            _board.field_size,
            WHITE_PIECE,
            STRAIGHT,
            vec2u(7, 7)
        ));
    _board.pieces.push_back(
        new Rook(
            _textures["rook"],
            _board.fields[7*8],
            _board.field_size,
            WHITE_PIECE,
            STRAIGHT,
            vec2u(0, 7)
        ));
    _board.pieces.push_back(
        new Knight(
            _textures["horse"],
            _board.fields[1],
            _board.field_size,
            BLACK_PIECE,
            JUMPY,
            vec2u(1,0)
        ));
    _board.pieces.push_back(
        new Knight(
            _textures["horse"],
            _board.fields[6],
            _board.field_size,
            BLACK_PIECE,
            JUMPY,
            vec2u(6, 0)
        ));
    _board.pieces.push_back(
        new Knight(
            _textures["horse"],
            _board.fields[1+8*7],
            _board.field_size,
            WHITE_PIECE,
            JUMPY,
            vec2u(1, 7)
        ));
    _board.pieces.push_back(
        new Knight(
            _textures["horse"],
            _board.fields[6+7*8],
            _board.field_size,
            WHITE_PIECE,
            JUMPY,
            vec2u(6, 7)
        ));

    _board.pieces.push_back(
        new Queen(
            _textures["queen"],
            _board.fields[3],
            _board.field_size,
            BLACK_PIECE,
            STRAIGHT | DIAGONAL,
            vec2u(3, 0)
        ));
    _board.pieces.push_back(
         new Queen(
            _textures["queen"],
            _board.fields[3 + 7 * 8],
            _board.field_size,
            WHITE_PIECE,
            STRAIGHT | DIAGONAL,
            vec2u(3, 7)
        ));

    _board.pieces.push_back(
        new King(
            _textures["king"],
            _board.fields[4],
            _board.field_size,
            BLACK_PIECE,
            STRAIGHT | DIAGONAL,
            vec2u(4, 0)
        ));
    _board.pieces.push_back(
        new King(
            _textures["king"],
            _board.fields[4 + 7 * 8],
            _board.field_size,
            WHITE_PIECE,
            STRAIGHT | DIAGONAL,
            vec2u(4, 7)
        ));

    _board.pieces.push_back(
        new Bishop(
            _textures["bishop"],
            _board.fields[2],
            _board.field_size,
            BLACK_PIECE,
            DIAGONAL,
            vec2u(2, 0)
        ));
    _board.pieces.push_back(
        new Bishop(
            _textures["bishop"],
            _board.fields[5],
            _board.field_size,
            BLACK_PIECE,
            DIAGONAL,
            vec2u(5, 0)
        ));
    _board.pieces.push_back(
         new Bishop(
            _textures["bishop"],
            _board.fields[2 + 8 * 7],
            _board.field_size,
            WHITE_PIECE,
            DIAGONAL,
            vec2u(2, 7)
        ));
    _board.pieces.push_back(
        new Bishop(
            _textures["bishop"],
            _board.fields[5 + 7 * 8],
            _board.field_size,
            WHITE_PIECE,
            DIAGONAL,
            vec2u(5, 7)
        ));
    for (auto& piece : _board.pieces) {
        if (piece->get_mtype() == MoveType::STRAIGHT || piece->is_king()) {
            piece->_castleable = true;
        }
        auto legal_moves = piece->find_legal_moves();
        auto corrected_legal_moves = _board.correct_legal_moves(legal_moves, piece);
        piece->set_legal_moves(corrected_legal_moves);
    }
}
void Game::match() {
    reset();
    sf::Clock clock;
    bool is_holding = false;
    bool is_smth_selected = false;
    bool check_legal_moves = false;
    bool was_king_checked = false;
    bool old_turn = State::whosturn();
    bool turn = State::whosturn();
    
    
    std::vector<vec2u> saveable = {};
    bool checkmate = false;
    int frame_count = 0;
    float frame_time = 0;
    sf::Event event;
    bool game_running = true;

    auto players = State::get_player();
    Player::end = false;
    std::thread white_t(&Player::decrement_time, players.first);
    std::thread black_t(&Player::decrement_time, players.second);


    bool white_ff = false;
    bool white_f = false;
    bool black_ff = false;
    bool black_f = false;
    bool white_draw = false;
    bool black_draw = false;
    bool drew = false;

    while (game_running) {
        turn = State::whosturn();
        Player::turn = turn;
        auto curr_player = State::get_player(turn);
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

                        bool player_color = turn;
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
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::C) {
                    // white draw
                    white_draw = true;
                }
                if (event.key.code == sf::Keyboard::V) {
                    // white forfeit
                    if (white_f) white_ff = true;
                    white_f = true;
                }
                if (event.key.code == sf::Keyboard::D) {
                    // black draw
                    black_draw = true;
                }
                if (event.key.code == sf::Keyboard::F) {
                    // black forfeit
                    if (black_f) black_ff = true;
                    black_f = true;
                }
                if (event.key.code == sf::Keyboard::Escape) {
                    black_f = false;
                    white_f = false;
                }
                break;
            default:
                break;
            }

        }
        white_f ? _renderer._forfeit2.setFillColor(sf::Color::Red) : _renderer._forfeit2.setFillColor(WHITE);
        black_f ? _renderer._forfeit1.setFillColor(sf::Color::Red) : _renderer._forfeit1.setFillColor(WHITE);
        white_draw ? _renderer._draw2.setFillColor(sf::Color::Yellow) : _renderer._draw2.setFillColor(WHITE);
        black_draw ? _renderer._draw1.setFillColor(sf::Color::Yellow) : _renderer._draw1.setFillColor(WHITE);

        State::set_under_attack({});
        auto king = _board.get_king_by_color(turn);
        for (auto& piece : _board.pieces) {
            if (piece->is_king()) continue;
            auto legal_moves = piece->find_legal_moves();
            auto corrected_legal_moves = _board.correct_legal_moves(legal_moves, piece);
            auto special_legal_moves = piece->special_legal_moves(corrected_legal_moves, _board.pieces, _board.fields);
            if (king->is_checked() && !piece->is_king() && piece->get_color() == turn) {
                auto intersect = _board.intersect(special_legal_moves, saveable);
                piece->set_legal_moves(intersect);
            }
            else {
                piece->set_legal_moves(special_legal_moves);
            }
            if (piece->get_color() != turn) {
                State::append_ua_fields(piece->get_legal_moves());
            }

        }
        auto legal_moves = king->find_legal_moves();
        auto corrected_legal_moves = _board.correct_legal_moves(legal_moves, king);
        auto special_legal_moves = king->special_legal_moves(corrected_legal_moves, _board.pieces, _board.fields);
        king->set_legal_moves(special_legal_moves);
        if (king->is_checked() && old_turn != turn) {
            Audio::push_event(AudioEvent::Check);
            saveable = _board.calc_saveable_fields();
        }

        _should_draw_legal_moves = false;
        vec2f selected_field = _board.get_selected();
        Piece* selected_piece = _board.get_piece_by_field(selected_field);
        if (is_holding) {
            if (selected_piece) {

                sf::Vector2i mouse_pos = sf::Mouse::getPosition(*_window);
                float mouse_x = (float)mouse_pos.x;
                float mouse_y = (float)mouse_pos.y;
                selected_piece->set_act_pos_mouse(mouse_x, mouse_y);

                _should_draw_legal_moves = true;
                std::vector<vec2f> legal_fields;
                auto push_lf = [&legal_fields, this](auto &item) {
                    legal_fields.push_back(_board.get_field_by_board_index(item));
                };
                std::ranges::for_each(selected_piece->get_legal_moves(), push_lf);
                _board.set_current_legal_fields(legal_fields);
            }
        }

        checkmate = true;
        for (auto& piece : _board.pieces) {
            if (piece->get_color() == turn) {
                if (piece->get_legal_moves().size() > 0) {
                    checkmate = false;
                }
            }
        }
        if (curr_player->get_time() == 0) {
            _view = View::Menu;
            game_running = false;
            Player::end = true;
            State::turn();
        }
        if (checkmate) {
            _view = View::Menu;
            game_running = false;
            Player::end = true;
        }
        if (white_draw && black_draw) {
            drew = true;
            _view = View::Menu;
            game_running = false;
            Player::end = true;
        }
        if (turn && (white_ff || black_ff)) {
            _view = View::Menu;
            game_running = false;
            Player::end = true;
            if (black_ff) {
                State::turn();
            }
        }
        else if(!turn && (white_ff || black_ff)) {
            _view = View::Menu;
            game_running = false;
            Player::end = true;
            if (white_ff) {
                State::turn();
            }
        }

        old_turn = turn;
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

        if (State::_castle == 1) {
            auto kingX = king->get_board_index().x;
            auto kingY = king->get_board_index().y;
            auto rook = _board.get_piece_by_field(_board.get_field_by_board_index(vec2u(7, kingY)));
            if (rook) {
                rook->set_board_index(vec2u(5, kingY));
                auto fieldX = _board.get_field_by_board_index(vec2u(5, kingY)).x;
                auto fieldY = _board.get_field_by_board_index(vec2u(5, kingY)).y;
                rook->set_field_pos(fieldX, fieldY);
                rook->_castleable = false;
                rook->update(_board.field_size, _board.fields);
            }
            State::_castle = 0;
        }
        if (State::_castle == 2) {
            auto kingX = king->get_board_index().x;
            auto kingY = king->get_board_index().y;
            auto rook = _board.get_piece_by_field(_board.get_field_by_board_index(vec2u(0, kingY)));
            if (rook) {
                rook->set_board_index(vec2u(3, kingY));
                auto fieldX = _board.get_field_by_board_index(vec2u(3, kingY)).x;
                auto fieldY = _board.get_field_by_board_index(vec2u(3, kingY)).y;
                rook->set_field_pos(fieldX, fieldY);
                rook->_castleable = false;
                rook->update(_board.field_size, _board.fields);
            }
            State::_castle = 0;
        }


    }
    if (drew) {
        State::_draw = true;
    }
    _renderer._forfeit2.setFillColor(WHITE);
    _renderer._forfeit1.setFillColor(WHITE);
    _renderer._draw2.setFillColor(WHITE);
    _renderer._draw1.setFillColor(WHITE);
    white_t.detach();
    black_t.detach();
    
}
void Game::run() {
    int close = 0;
    bool play_again = false;
    if (!_window) return;
    
    load_textures();

    while (_window->isOpen()) {
        switch (_view) {
        case View::Match:
            match();
            _view = View::Endgame;
            break;
        case View::Menu:
            close = _menu_view.loop();
            if (!close) _view = View::Match;
            break;
        case View::Endgame:
            play_again = _menu_view.endgame();
            play_again ? _view = View::Match : _view = View::Menu;
            break;
        }
        if (close) {
            break;
        }
    }
    

}

void Game::update() {
    _board.update();
    _renderer.update_texts(_fps);
}



void Game::render() {
    _window->clear(MenuColors::BACKGROUND);
    _board.draw(*_window);
    _renderer.draw(*_window);
    if (_should_draw_legal_moves) {
        _board.draw_legal_fields(*_window);
    }
    for (auto &piece : _board.pieces) {
        piece->draw(*_window);
    }
    Piece* selected_piece = _board.get_piece_by_field(_board.get_selected());
    if (selected_piece) {
        selected_piece->draw(*_window);
    }
    _window->display();
}

