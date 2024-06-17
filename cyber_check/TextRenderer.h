#pragma once
#include"cdef.h"
#include"state/State.h"
struct PlayerSection {
	sf::Text name;
	sf::Text score;
	sf::Text time;
};
class TextRenderer {
	sf::Text _fps_text;
	sf::Text _whos_turn_text;
	PlayerSection _player1;
	PlayerSection _player2;
	sf::Font _font;
	vec2f _board_pos;
	int _board_size;
public:
	sf::Text _draw1;
	sf::Text _forfeit1;
	sf::Text _draw2;
	sf::Text _forfeit2;
	void draw(sf::RenderWindow &window);
	void update_texts(float fps);
	TextRenderer();
	TextRenderer(vec2f board_pos, int board_size, std::string font_path);

};