#include "Board.h"
Board::Board() {
    field_size = 0;
}

Board::Board(const sf::RenderWindow& window) {
    vec2u cords = window.getSize();
    float y_eight = ((float)cords.y / 10.0f);
    float inline_margin = ((float)cords.x - 8.0f * y_eight) / 2.0f;
    float horizontal_margin = ((float)cords.y - 8.0f * y_eight) / 2.0f;

    for (size_t i = 0; i < 8; i++) {
        for (size_t j = 0; j < 8; j++) {
            uint32_t x = j * y_eight + inline_margin;
            uint32_t y = i * y_eight + horizontal_margin;
            fields.push_back(vec2f(x, y));
        }
    }
    field_size = y_eight;
    _hovered_field = fields[0];
    _selected_field = vec2f(-1.0, -1.0);
}

vec2f Board::get_hovered() {
    return _hovered_field;
}

void Board::set_hovered(vec2f field) {
    
    _hovered_field = field;
}

vec2f Board::get_selected() {
    return _selected_field;
}

void Board::set_selected(vec2f field) {

    _selected_field = field;
}

void Board::set_current_legal_fields(const std::vector<vec2f>& fields) {
    _current_legal_fields = fields;
}


vec2f Board::get_field_by_mouse_cords(uint32_t x, uint32_t y) {
    for (auto &field : fields) {
        if ((x > field.x && x < field.x + field_size) && (y > field.y && y < field.y + field_size)) return field;
    }
    return _hovered_field;
}

vec2f Board::get_field_by_board_index(vec2u board_index) {
    uint32_t index = board_index.x + board_index.y * 8;
    return fields[index];
}

Piece* Board::get_piece_by_field(vec2f field) {
    for (auto const &piece : pieces) {
        vec2f piece_pos = piece->get_field_pos();
        if (field.x == piece_pos.x && field.y == piece_pos.y) {
            return piece;
        }
    }
    return nullptr;
}
std::vector<Piece*>* Board::get_pieces() {
    return &pieces;
}
std::vector<std::vector<vec2u>> Board::sort_lm_by_selected_piece(const std::vector<vec2u>& legal_moves, Piece* selected_piece) {
    std::vector<std::vector<vec2u>> sorted_by_selpos_lm;
    auto sel_move_type = selected_piece->get_mtype();
    auto selPOS = selected_piece->get_board_index();
    auto selX = selPOS.x;
    auto selY = selPOS.y;
    if (sel_move_type & JUMPY) {
        sorted_by_selpos_lm.push_back(legal_moves);
    }
    if (sel_move_type & DIAGONAL) {
        std::vector<vec2u> lu;
        std::vector<vec2u> ld;
        std::vector<vec2u> ru;
        std::vector<vec2u> rd;
        for (auto &legal_move : legal_moves) {
            if (legal_move.y < selY && legal_move.x < selX) {
                lu.insert(lu.begin(), legal_move);
            }
            if (legal_move.y < selY && legal_move.x > selX) {
                ru.push_back(legal_move);
            }

            if (legal_move.y > selY && legal_move.x < selX) {
                ld.insert(ld.begin(), legal_move);
            }
            if (legal_move.y > selY && legal_move.x > selX) {
                rd.push_back(legal_move);
            }
        }
        sorted_by_selpos_lm.push_back(lu);
        sorted_by_selpos_lm.push_back(ld);
        sorted_by_selpos_lm.push_back(ru);
        sorted_by_selpos_lm.push_back(rd);

    }
    if (sel_move_type & STRAIGHT || sel_move_type & PAWN) {
        std::vector<vec2u> l;
        std::vector<vec2u> u;
        std::vector<vec2u> r;
        std::vector<vec2u> d;
        for (auto &legal_move : legal_moves) {
            if (legal_move.y == selY && legal_move.x < selX) {
                l.insert(l.begin(), legal_move);
            }
            if (legal_move.y == selY && legal_move.x > selX) {
                r.push_back(legal_move);
            }
            if (legal_move.y < selY && legal_move.x == selX) {
                u.insert(u.begin(), legal_move);
            }
            if (legal_move.y > selY && legal_move.x == selX) {
                d.push_back(legal_move);
            }
        }
        sorted_by_selpos_lm.push_back(l);
        sorted_by_selpos_lm.push_back(r);
        sorted_by_selpos_lm.push_back(u);
        sorted_by_selpos_lm.push_back(d);
    }

    return sorted_by_selpos_lm;
}



std::vector<vec2u> Board::correct_legal_moves(const std::vector<vec2u>& legal_moves, Piece* selected_piece) {
    std::vector<vec2u> corrected;
    auto sorted_legal_moves_by_selected = sort_lm_by_selected_piece(legal_moves, selected_piece);


    bool found = false;
    bool ally = false;
    bool is_king = false;
    bool is_pieces_turn = State::whosturn();
    if (selected_piece->get_mtype() & JUMPY) {
    
        for (auto& moves : sorted_legal_moves_by_selected) {
         
            for (auto& move : moves) {
                for (auto& piece : pieces) {
                    ally = selected_piece->get_color() == piece->get_color();
                    if (move.x == piece->get_board_index().x && move.y == piece->get_board_index().y && ally) {
                        found = true;
                    }
                }
                if (!found) {
                    corrected.push_back(move);
                }
                else if (found && ally && selected_piece->get_color() == !is_pieces_turn) {
                    corrected.push_back(move);
                }
                found = false;
            }
        }
        return corrected;
    }
    

    found = false;

    for (auto &moves : sorted_legal_moves_by_selected) {
        for (auto &move : moves) {
            found = false;
            for (auto &piece : pieces) {
                is_king = piece->is_king();
                ally = selected_piece->get_color() == piece->get_color();
                if (is_king && !ally) {
                    continue;
                }
                if (move.x == piece->get_board_index().x && move.y == piece->get_board_index().y) {
                    found = true;
                    break;
                }
            }
            if (found) {
                if (!ally) {
                    corrected.push_back(move);
                }
                if (selected_piece->get_color() == !is_pieces_turn) {
                    corrected.push_back(move);
                }
                break;
            }
            corrected.push_back(move);
        }
    }
    return corrected;
}
std::vector<int> Board::get_pieceidx_by_boardidx(vec2u board_idx) {
    std::vector<int> res;
    for (size_t i = 0; i < pieces.size(); i++) {
        if (pieces[i]->get_board_index() == board_idx) {
            res.push_back(i);
        }
    }
    return res;
}
Piece* Board::get_king_by_color(bool color) {
    for (auto& piece : pieces) {
        if (piece->is_king() && piece->get_color() == color) {
            return piece;
        }
    }
    return nullptr;
}
std::vector<vec2u> Board::calc_saveable_fields() {
    bool turn = State::whosturn();
    std::vector<vec2u> saveable_fields = {};
    std::vector<vec2u> tmp_saveable = {};
    std::vector<Piece*> attacking_pieces = {};
    Piece *king = get_king_by_color(turn);
    if (king == nullptr) return saveable_fields;
    int kingX = king->get_board_index().x;
    int kingY = king->get_board_index().y;
    for (auto& piece : pieces) {
        bool next_piece = false;
        int pieceX = piece->get_board_index().x;
        int pieceY = piece->get_board_index().y;
        MoveType mtype = piece->get_mtype();
        if (mtype & MoveType::STRAIGHT || mtype &MoveType::DIAGONAL) {
                auto sorted_moves = sort_lm_by_selected_piece(piece->get_legal_moves(), piece);
                // bishop seems good, queen seems weird now, need to test rook and implement horse
                if (mtype & MoveType::DIAGONAL) {
                    std::reverse(sorted_moves[0].begin(), sorted_moves[0].end());
                    std::reverse(sorted_moves[1].begin(), sorted_moves[1].end());
                }
                if (mtype & MoveType::STRAIGHT) {
                    if (sorted_moves.size() == 8) {

                        std::reverse(sorted_moves[4].begin(), sorted_moves[4].end());
                        std::reverse(sorted_moves[6].begin(), sorted_moves[6].end());
                    }
                    else {
                        std::reverse(sorted_moves[0].begin(), sorted_moves[0].end());
                        std::reverse(sorted_moves[2].begin(), sorted_moves[2].end());
                    }
                }

                
                
                for (auto& moves : sorted_moves) {
                    if (next_piece) continue;
                    for (auto& move : moves) {
                        if (pieceX > kingX && move.x > pieceX) continue;
                        if (pieceX < kingX && move.x < pieceX) continue;
                        if (pieceY < kingY && move.y < pieceY) continue;
                        if (pieceY > kingY && move.y > pieceY) continue;
                        
                        tmp_saveable.push_back(move);
                        Piece* this_field_piece = get_piece_by_field(get_field_by_board_index(move));
                        if (this_field_piece != nullptr && this_field_piece != king) {
                            tmp_saveable.clear();
                            continue;
                        }
                        if (this_field_piece == king) {
                            tmp_saveable.pop_back();
                            saveable_fields.insert(saveable_fields.end(), tmp_saveable.begin(), tmp_saveable.end());
                            attacking_pieces.push_back(piece);
                            next_piece = true;
                            break;
                        }

                    }
                }

                if (next_piece) continue;
            //}

        }
    }
    if (attacking_pieces.size() == 1) {
        saveable_fields.push_back(attacking_pieces[0]->get_board_index());
    }
    return saveable_fields;

}

void Board::update() {
    for (auto const &piece : pieces) {
        bool hit = false;
        bool piece_color = piece->get_color();
        if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            int res = piece->update(field_size, fields);
            if (res) {
                auto piece_idxs = get_pieceidx_by_boardidx(piece->get_board_index());
                if (piece_idxs.size() > 1) {
                    for (auto& idx : piece_idxs) {
                        if (pieces[idx]->get_color() != piece_color) {
                            int new_value = pieces[idx]->get_value();
                            int state_score = State::get_score();
                            State::set_score(state_score + (piece_color ? new_value : new_value * -1));
                            hit = true;
                            pieces.erase(pieces.begin() + idx);
                            break;
                        }
                    }
                }
                if (State::check()) {
                    Audio::push_event(AudioEvent::Check);
                    continue;
                }
                hit ? Audio::push_event(AudioEvent::Hit) : Audio::push_event(AudioEvent::Place);
            }
        }
    }
    
}
bool less_than_vec2u(const vec2u lhs, const vec2u rhs) {
    return std::tie(lhs.x, lhs.y) < std::tie(rhs.x, rhs.y);
}
std::vector<vec2u> Board::intersect(std::vector<vec2u> fields1, std::vector<vec2u> fields2) {
    std::sort(fields1.begin(), fields1.end(), less_than_vec2u);
    std::sort(fields2.begin(), fields2.end(), less_than_vec2u);

    std::vector<sf::Vector2u> result;

    std::set_intersection(fields1.begin(), fields1.end(),
        fields2.begin(), fields2.end(),
        std::back_inserter(result),
        less_than_vec2u);

    return result;
}

void Board::draw_legal_fields(sf::RenderWindow& window) {
    for (size_t i = 0; i < _current_legal_fields.size(); i++) {
        sf::RectangleShape rect(vec2f(field_size - 5, field_size - 5));
        sf::Color field_color = sf::Color::Red;
        field_color.a = 128;
        rect.setFillColor(field_color);
        rect.setPosition(_current_legal_fields[i].x, _current_legal_fields[i].y);
        window.draw(rect);
    }
}

void Board::draw(sf::RenderWindow& window) {
    for (size_t i = 0; i < fields.size(); i++) {
        sf::RectangleShape rect(vec2f(field_size - 5, field_size - 5));
        sf::Color field_color = (i / 8 + i % 8) % 2 == 0 ? BLACK : WHITE;
        rect.setFillColor(field_color);

        rect.setPosition(fields[i].x, fields[i].y);
        window.draw(rect);
    }
    sf::RectangleShape hovered(sf::Vector2f(field_size - 5, field_size - 5));
    hovered.setPosition(_hovered_field.x, _hovered_field.y);
    hovered.setOutlineColor(sf::Color::Yellow);
    hovered.setOutlineThickness(5);
    hovered.setFillColor(sf::Color::Transparent);
    window.draw(hovered);
}
