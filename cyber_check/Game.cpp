#include"Game.h"
Game::Game(sf::VideoMode vm, const sf::String& title, std::string font_path) {
    if (!font.loadFromFile(font_path)) {
        std::cerr << "couldnt load font, exiting now";
        exit(1);
    }
    _window = new sf::RenderWindow(vm, title, sf::Style::Resize | sf::Style::Fullscreen);
    _board = Board(*_window);
    _state = State::MENU;
    _should_draw_legal_moves = false;
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

void Game::push_piece(uint32_t x, uint32_t y, sf::Color color, PieceType pt) {
    switch (pt) {
    case PieceType::ROOK:
        if (true) {
            Piece* rook_piece = new Rook(
                _textures["rook"],
                _board.fields[y * 8 + x],
                _board.field_size,
                color,
                vec2u(x, y)
            );
            rook_piece->set_legal_moves(rook_piece->find_legal_moves());
            _board.pieces.push_back(std::make_pair(vec2u(x, y), rook_piece));
        }
        break;
        
    case PieceType::BISHOP:
        if (true) {
            Piece* bishop_piece = new Bishop(
                _textures["bishop"],
                _board.fields[y * 8 + x],
                _board.field_size,
                color,
                vec2u(x, y)
            );
            bishop_piece->set_legal_moves(bishop_piece->find_legal_moves());
            _board.pieces.push_back(std::make_pair(vec2u(x, y), bishop_piece));
        }
        break;
    case PieceType::HORSE:
        if (true) {
            Piece* knight_piece = new Knight(
                _textures["horse"],
                _board.fields[y * 8 + x],
                _board.field_size,
                color,
                vec2u(x, y)
            );
            knight_piece->set_legal_moves(knight_piece->find_legal_moves());
            _board.pieces.push_back(std::make_pair(vec2u(x, y), knight_piece));
        }
        break;
    case PieceType::KING:
        if (true) {
            Piece* king_piece = new King(
                _textures["king"],
                _board.fields[y * 8 + x],
                _board.field_size,
                color,
                vec2u(x, y)
            );
            king_piece->set_legal_moves(king_piece->find_legal_moves());
            _board.pieces.push_back(std::make_pair(vec2u(x, y), king_piece));
        }
        break;

    case PieceType::QUEEN:
        if (true) {
            Piece* queen_piece = new Queen(
                    _textures["queen"],
                    _board.fields[y * 8 + x],
                    _board.field_size,
                    color,
                    vec2u(x, y)
                    );
            queen_piece->set_legal_moves(queen_piece->find_legal_moves());
            _board.pieces.push_back(std::make_pair(vec2u(x, y), queen_piece));
        }
        break;

    default:
        Piece* rook_piece = new Rook(
            _textures["pawn"], 
            _board.fields[y*8 + x], 
            _board.field_size, 
            color,
            vec2u(x, y)
            );
        rook_piece->set_legal_moves(rook_piece->find_legal_moves());
        _board.pieces.push_back(std::make_pair(vec2u(x,y), rook_piece));
        break;
    }

    
}

void Game::reset() {

    for (size_t i = 0 ; i < 8; i++) {
        push_piece(i, 1, BLACK_PIECE, PieceType::PAWN);
    }
    for (size_t i = 0; i < 8; i++) {
        push_piece(i, 6, WHITE_PIECE, PieceType::PAWN);
    }

    push_piece(0,0, BLACK_PIECE, PieceType::ROOK);
    push_piece(7,0, BLACK_PIECE, PieceType::ROOK);
    push_piece(0, 7, WHITE_PIECE, PieceType::ROOK);
    push_piece(7, 7, WHITE_PIECE, PieceType::ROOK);

    push_piece(1, 0, BLACK_PIECE, PieceType::HORSE);
    push_piece(6, 0, BLACK_PIECE, PieceType::HORSE);
    push_piece(1, 7, WHITE_PIECE, PieceType::HORSE);
    push_piece(6, 7, WHITE_PIECE, PieceType::HORSE);

    push_piece(3, 0, BLACK_PIECE, PieceType::QUEEN);
    push_piece(3, 7, WHITE_PIECE, PieceType::QUEEN);

    push_piece(4, 0, BLACK_PIECE, PieceType::KING);
    push_piece(4, 7, WHITE_PIECE, PieceType::KING);

    push_piece(2, 0, BLACK_PIECE, PieceType::BISHOP);
    push_piece(5, 0, BLACK_PIECE, PieceType::BISHOP);
    push_piece(2, 7, WHITE_PIECE, PieceType::BISHOP);
    push_piece(5, 7, WHITE_PIECE, PieceType::BISHOP);
}

void Game::run() {
    if (!_window) return;
    sf::Clock clock;
    bool is_holding = false;
    bool is_smth_selected = false;
    bool drop = false;
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
                        _board.set_selected(_board.get_hovered());
                        is_smth_selected = true;
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if (is_holding) {
                    is_holding = false;
                    is_smth_selected = false;
                    drop = true;
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
                vec2u board_index = selected_piece->get_board_index();
                selected_piece->set_legal_moves(selected_piece->find_legal_moves());

                _should_draw_legal_moves = true;
                std::vector<vec2f> legal_fields;
                for (auto &legal_move : selected_piece->get_legal_moves()) {
                    legal_fields.push_back(_board.get_field_by_board_index(legal_move));
                }
                _board.set_current_legal_fields(legal_fields);
            }
            else {
                _should_draw_legal_moves = false;
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
}



void Game::render() {
    _window->clear(sf::Color::Black);

    sf::Text text;
    text.setFont(font);
    text.setFillColor(BLACK);
    text.setString(std::to_string(_fps));
    text.setPosition(10.0f, 10.0f);
    _window->draw(text);

    _board.draw(*_window);
    if (_should_draw_legal_moves) {
        _board.draw_legal_fields(*_window);
    }
    for (auto &piece : _board.pieces) {
        piece.second->draw(*_window);
    }
    _window->display();
}

