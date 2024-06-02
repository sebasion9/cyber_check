#include"TextRenderer.h"


void TextRenderer::draw(sf::RenderWindow& window) {
    window.draw(_fps_text);
    window.draw(_whos_turn_text);

    window.draw(_player1.name);
    window.draw(_player1.score);
    window.draw(_player1.time);

    window.draw(_player2.name);
    window.draw(_player2.score);
    window.draw(_player2.time);
}

void TextRenderer::update_texts(float fps) {
    _fps_text.setString("fps " + std::to_string((int)fps));
    _fps_text.setFont(_font);
    int state_score = State::get_score();
    int score_flag = state_score < 0 && state_score != 0;
    _player1.name.setFont(_font);
    _player1.score.setFont(_font);
    _player1.score.setString(score_flag ? "+" + std::to_string(abs(state_score)) : "");
    // DBG
    _player1.time.setFont(_font);
    _player1.time.setString("3:00");

    _player2.name.setFont(_font);
    _player2.score.setFont(_font);
    _player2.score.setString(score_flag ? "" : "+" + std::to_string(abs(state_score)));
    // DBG
    _player2.time.setFont(_font);
    _player2.time.setString("3:00");

    _whos_turn_text.setString(State::whosturn() ? "white turn" : "black turn");
    _whos_turn_text.setFillColor(State::whosturn() ? WHITE : BLACK);
    auto whosturnY = _board_pos.y - (double)SPACING::BOARD_OFFSET + (double)_board_size / 2.0 - SPACING::BOARD_OFFSET / 2.0;
    auto whosturnX = State::whosturn() ? _player2.time.getGlobalBounds().left + _player2.time.getGlobalBounds().width
        : _player1.time.getGlobalBounds().left + _player1.time.getGlobalBounds().width;
    whosturnX += 2 * SPACING::MARGIN;
    _whos_turn_text.setPosition(vec2f(
        whosturnX,
        whosturnY
    ));
    _whos_turn_text.setFont(_font);
}
TextRenderer::TextRenderer() {
	_board_pos = vec2f(0,0);
	_board_size = 0;

}

TextRenderer::TextRenderer(vec2f board_pos, int board_size, std::string font_path) {
    if (!_font.loadFromFile(font_path)) {
        std::cerr << "couldnt load font, exiting now";
        exit(1);
    }
	_board_pos = board_pos;
	_board_size = board_size;

    sf::Text fps;
    fps.setFillColor(WHITE_PIECE);
    std::string fps_string = "fps 000";
    fps_string.append(std::to_string((int)0));
    fps.setString(fps_string);
    fps.setPosition(SPACING::MARGIN, SPACING::MARGIN);

    _fps_text = fps;


    auto fps_bounds = fps.getGlobalBounds();
    auto fps_right = fps_bounds.left + fps_bounds.width;
    auto fps_bot = fps_bounds.top + fps_bounds.height;


    // PLAYER NAME, SCORE, TIME
    player_pair players = State::get_player();
    
    sf::Text player1_name;
    sf::Text player1_time;
    sf::Text player1_score;
    sf::Text player2_name;
    sf::Text player2_time;
    sf::Text player2_score;

    player1_name.setFillColor(BLACK);
    player1_name.setString(players.first->get_name());
    player1_name.setPosition(vec2f(
        _board_pos.x + (double)_board_size + SPACING::MARGIN,
        _board_pos.y - SPACING::BOARD_OFFSET + (double)_board_size * 3.0/8.0));

    player1_score.setFillColor(BLACK);
    //
    player1_score.setString("");
    //
    player1_score.setPosition(vec2f(
        _board_pos.x + (double)_board_size + SPACING::MARGIN,
        player1_name.getGlobalBounds().top + (double)_board_size/8.0/2.0 - SPACING::BOARD_OFFSET
    ));
    player1_time.setFillColor(BLACK);
    player1_time.setString(std::to_string(players.first->get_time()));
    player1_time.setPosition(vec2f(
        _board_pos.x + (double)_board_size + SPACING::MARGIN,
        player1_score.getGlobalBounds().top + (double)_board_size/8.0/2.0 - SPACING::MARGIN
    ));

    _player1 = PlayerSection{
    player1_name,player1_score,player1_time
    };

    player2_time.setFillColor(WHITE);
    player2_time.setString(std::to_string(players.second->get_time()));
    player2_time.setPosition(vec2f(
        _board_pos.x + (double)_board_size + SPACING::MARGIN,
        _board_pos.y - SPACING::BOARD_OFFSET + (double)_board_size / 2.0));
    
    player2_score.setFillColor(WHITE);
    //
    player2_score.setString("");
    //
    player2_score.setPosition(vec2f(
        _board_pos.x + (double)_board_size + SPACING::MARGIN,
        player2_time.getGlobalBounds().top + (double)_board_size / 8.0 / 2.0 - SPACING::BOARD_OFFSET
    ));

    player2_name.setFillColor(WHITE);
    player2_name.setString(players.second->get_name());
    player2_name.setPosition(vec2f(
        _board_pos.x + (double)_board_size + SPACING::MARGIN,
        player2_score.getGlobalBounds().top + (double)_board_size / 8.0 / 2.0 - SPACING::MARGIN
    ));



    _player2 = PlayerSection{
        player2_name,player2_score,player2_time
    };


    // WHO'S TURN

    sf::Text whos_turn;
    whos_turn.setFillColor(State::whosturn() ? WHITE : BLACK);
    std::string whos_turn_string = State::whosturn() ? "white" : "black";
    whos_turn_string.append(" turn");
    whos_turn.setString(whos_turn_string);
    whos_turn.setPosition(vec2f(
        player2_time.getGlobalBounds().left + player2_time.getGlobalBounds().width, 
        _board_pos.y - SPACING::BOARD_OFFSET + (double)_board_size / 2.0
    ));
    _whos_turn_text = whos_turn;
}