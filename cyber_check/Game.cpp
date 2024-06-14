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

    while (game_running) {
        turn = State::whosturn();
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
            default:
                break;
            }

        }
        State::set_under_attack({});
        auto king = _board.get_king_by_color(turn);
        for (auto& piece : _board.pieces) {
            if (piece->is_king()) continue;
            auto legal_moves = piece->find_legal_moves();
            auto corrected_legal_moves = _board.correct_legal_moves(legal_moves, piece);
            auto special_legal_moves = piece->special_legal_moves(corrected_legal_moves, _board.pieces);
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
        auto special_legal_moves = king->special_legal_moves(corrected_legal_moves, _board.pieces);
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
                for (auto& legal_move : selected_piece->get_legal_moves()) {
                    legal_fields.push_back(_board.get_field_by_board_index(legal_move));
                }

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
        if (checkmate) {
            _view = View::Menu;
            break;
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
    }
    
    

}
void Game::run() {
    int close = 0;
    if (!_window) return;
    
    load_textures();

    while (_window->isOpen()) {
        switch (_view) {
        case View::Match:
            match();
            break;
        case View::Menu:
            close = _menu_view.loop();
            break;
        default:
            //menu
            break;
        }

        if (close) {
            break;
        }
        else {
            _view = View::Match;
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

