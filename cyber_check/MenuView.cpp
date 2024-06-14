#include"MenuView.h"

MenuView::MenuView() {
}

MenuView::MenuView(sf::RenderWindow* win, const std::string &font_path) {
	if (!font.loadFromFile(font_path)) {
		std::cerr << "couldnt load font, exiting now";
		exit(1);
	}
	_window = win;
}
void MenuView::init_text(const std::string& txt_str, sf::FloatRect rect) {
	auto win_size = _window->getSize();
	auto w = win_size.x / 4.0f;
	auto h = win_size.y * 4.0f / 5.0f;
	auto x = 1.5 * w;
	auto y = win_size.y / 6.0f;

	sf::Text* text = new sf::Text;
	text->setFont(font);
	text->setFillColor(MenuColors::TEXT_PRIMARY);
	text->setString(txt_str);
	text->setScale(1.5f, 1.5f);
	sf::FloatRect gt_rect = text->getLocalBounds();
	text->setOrigin(gt_rect.left + gt_rect.width / 2.0f,
		gt_rect.top + gt_rect.height / 2.0f);
	text->setPosition(vec2f(rect.left + rect.width / 2.0f,
		rect.top + rect.height / 2.0f));
	_texts.push_back(text);
}
sf::FloatRect MenuView::init_rect(int idx) {
	auto win_size = _window->getSize();
	auto w = win_size.x / 4.0f;
	auto h = win_size.y * 4.0f / 5.0f;
	auto x = 1.5 * w;
	auto y = win_size.y / 6.0f;
	sf::RectangleShape* rect = new sf::RectangleShape(vec2f(w * 3 / 4, h / 10));
	auto gt_rect = rect->getLocalBounds();
	rect->setFillColor(MenuColors::SECONDARY);
	rect->setPosition(vec2f(x + w / 2 - gt_rect.width / 2, y + (idx*2+2) * h / 10.0f));

	_drawables.push_back(rect);

	return rect->getGlobalBounds();
}
sf::FloatRect MenuView::init_rect(int idx, sf::FloatRect dest) {
	auto win_size = _window->getSize();
	auto w = dest.width;
	auto h = dest.height;
	auto x = dest.left;
	auto y = dest.top;
	sf::RectangleShape* rect = new sf::RectangleShape(vec2f(w * 3 / 4, h / 10));
	auto gt_rect = rect->getLocalBounds();
	rect->setFillColor(MenuColors::SECONDARY);
	rect->setPosition(vec2f(x + w / 2 - gt_rect.width / 2, y + (idx * 2 + 2) * h / 10.0f));

	_drawables.push_back(rect);

	return rect->getGlobalBounds();
}

void MenuView::init_pieces() {
	auto win_size = _window->getSize();
	auto winX = win_size.x;
	auto winY = win_size.y;
	std::unordered_map<std::string, sf::Texture*> piece_textures = AssetLoader::load_textures();
	auto rook_txt = piece_textures["rook"];
	auto knight_txt = piece_textures["horse"];
	auto bishop_txt = piece_textures["bishop"];
	auto pawn_txt = piece_textures["pawn"];
	sf::Sprite* rook_spr = new sf::Sprite;
	sf::Sprite* knight_spr = new sf::Sprite;
	sf::Sprite* bishop_spr = new sf::Sprite;
	sf::Sprite* pawn_spr = new sf::Sprite;

	rook_spr->setTexture(*rook_txt);
	knight_spr->setTexture(*knight_txt);
	bishop_spr->setTexture(*bishop_txt);
	pawn_spr->setTexture(*pawn_txt);

	rook_spr->setColor(WHITE_PIECE);
	knight_spr->setColor(BLACK_PIECE);
	bishop_spr->setColor(WHITE_PIECE);
	pawn_spr->setColor(BLACK_PIECE);

	rook_spr->setPosition(winX / 10.0f, winY / 5.0f);
	rook_spr->setScale(20.0f, 20.0f);
	rook_spr->rotate(-45.0f);

	knight_spr->setPosition(winX * 9 / 10.0f, winY / 4.0f);
	knight_spr->setScale(25.0f, 25.0f);
	knight_spr->rotate(29.0f);


	bishop_spr->setPosition(winX * 3 / 10.0f, winY * 5.0f / 7.0f);
	bishop_spr->setScale(15.0f, 15.0f);
	bishop_spr->rotate(90.0f);

	pawn_spr->setPosition(winX * 7/ 10.0f, winY * 4.0f / 7.0f);
	pawn_spr->setScale(15.0f, 15.0f);

	_pieces.push_back(rook_spr);
	_pieces.push_back(knight_spr);
	_pieces.push_back(bishop_spr);
	_pieces.push_back(pawn_spr);
}


int MenuView::loop() {
	sf::Clock clock;
	int frame_count = 0;
	float frame_time = 0;
	sel_idx = -1;

	main_menu();
	bool gradient_down = false;
	auto title_color = MenuColors::TEXT_PRIMARY;
	auto menu_outline_color = MenuColors::SECONDARY;
	sf::Text* game_title_text = _texts[MainText::game_title];
	sf::RectangleShape* menu_outline = (sf::RectangleShape*)_drawables[MainBtn::menu_rect];
	sf::Event event;
	for (;;) {
		while(_window->pollEvent(event)) {
			switch (event.type) {
			case sf::Event::MouseButtonPressed:
				if (sel_idx == 1) {
					if (!play_menu()) {
						return 0;
					}
					main_menu();
					break;
				}
				if (sel_idx == 2) {
					opts();
					break;
				}
				if (sel_idx == 3) {
					leaderboard();
					std::cout << "leaderboard";
					break;
				}
				if (sel_idx == 4) {
					// exit
					return 1;
					break;
				}
				break;
			}
		
		}
		float delta_time = clock.restart().asSeconds();

		frame_count++;
		frame_time += delta_time;

		if (frame_time > 0.03f) {
			if (title_color.r == 254) {
				gradient_down = true;
			}
			if (title_color.r == 1) {
				gradient_down = false;
			}
			gradient_down ? title_color.r -= 1 : title_color.r += 1;
			game_title_text->setFillColor(title_color);
			menu_outline->setOutlineColor(title_color);
			frame_count = 0;
			frame_time = 0.0f;
		}
		clear_btns();
		color_hover();
		draw();
		update();
	}
}
void MenuView::color_hover() {
	if (sel_idx != -1) {
		sf::RectangleShape* button = (sf::RectangleShape*)_drawables[sel_idx];
		button->setFillColor(MenuColors::HOVER);
	}
}
void MenuView::color_select(int selected) {
	if (selected != -1) {
		sf::RectangleShape* button = (sf::RectangleShape*)_drawables[selected];
		button->setFillColor(MenuColors::SELECT);
	}
}
void MenuView::clear_btns() {
	sf::RectangleShape* rect_but;
	for (size_t i = 1; i < _drawables.size(); i++) {
		if (i == PlayBtn::second_box || i == PlayBtn::label1 || i == PlayBtn::label2) continue;
		rect_but = (sf::RectangleShape*)_drawables[i];
		rect_but->setFillColor(MenuColors::SECONDARY);
	}
}
void MenuView::clear_mem() {
	_drawables.clear();
	_texts.clear();
}
void MenuView::menu_box() {
	auto win_size = _window->getSize();
	auto w = win_size.x / 4.0f;
	auto h = win_size.y * 4.0f / 5.0f;
	auto x = 1.5 * w;
	auto y = win_size.y / 6.0f;
	sf::RectangleShape* menu_rect = new sf::RectangleShape(vec2f(w, h));
	menu_rect->setFillColor(MenuColors::PRIMARY);
	menu_rect->setOutlineThickness(-5.0f);
	menu_rect->setOutlineColor(MenuColors::SECONDARY);
	menu_rect->setPosition(vec2f(x, y));
	_drawables.push_back(menu_rect);
}
void MenuView::main_menu() {
	auto win_size = _window->getSize();
	auto w = win_size.x / 4.0f;
	auto h = win_size.y * 4.0f / 5.0f;
	auto x = 1.5 * w;
	auto y = win_size.y / 6.0f;
	auto title_color = MenuColors::TEXT_PRIMARY;
	sf::Text* game_title = new sf::Text;
	game_title->setFont(font);
	game_title->setFillColor(MenuColors::TEXT_PRIMARY);
	game_title->setString("cyber check");
	game_title->setScale(1.5f, 1.5f);
	sf::FloatRect gt_rect = game_title->getLocalBounds();
	game_title->setOrigin(gt_rect.left + gt_rect.width / 2.0f,
		gt_rect.top + gt_rect.height / 2.0f);
	game_title->setPosition(vec2f(x + w / 2.0f, y + h / 10.0f));
	_texts.push_back(game_title);

	menu_box();
	auto play_rect = init_rect(0);
	auto opts_rect = init_rect(1);
	auto leaderboard_rect = init_rect(2);
	auto exit_rect = init_rect(3);
	init_text("play", play_rect);
	init_text("options", opts_rect);
	init_text("leaderboard", leaderboard_rect);
	init_text("exit", exit_rect);
	init_pieces();
}

int MenuView::play_menu() {
	clear_mem();
	menu_box();
	auto t1 = init_rect(0);
	auto t2 = init_rect(1);
	auto t3 = init_rect(2);
	auto back = init_rect(3);
	init_text("3:00", t1);
	init_text("5:00", t2);
	init_text("10:00", t3);
	init_text("back", back);

	auto win_size = _window->getSize();
	auto w = win_size.x / 4.0f;
	auto h = win_size.y * 4.0f / 5.0f;
	auto x = 1.5 * w;
	auto y = win_size.y / 6.0f;
	sf::RectangleShape* form = new sf::RectangleShape(vec2f(w, h / 2));
	auto gt_rect = form->getLocalBounds();
	form->setFillColor(MenuColors::PRIMARY);
	form->setPosition(vec2f(x + w + SPACING::MENU_MARGIN, y));
	_drawables.push_back(form);
	
	auto label1 = init_rect(0, form->getGlobalBounds());
	auto input1 = init_rect(1, form->getGlobalBounds());
	auto label2 = init_rect(2, form->getGlobalBounds());
	auto input2 = init_rect(3, form->getGlobalBounds());

	auto play_btn = init_rect(5, form->getGlobalBounds());

	init_text("player 1", label1);
	init_text("white...", input1);
	init_text("player 2", label2);
	init_text("black...", input2);

	init_text("play", play_btn);

	_texts[PlayText::name1]->setFillColor(MenuColors::PRIMARY);
	_texts[PlayText::name2]->setFillColor(MenuColors::PRIMARY);

	int selected_time = -1;

	sf::Event event;
	for (;;) {
		while (_window->pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				if (sel_idx == PlayBtn::back) {
					clear_mem();
					return 1;
				}
				if (sel_idx == PlayBtn::label1 || sel_idx == PlayBtn::label2) {
					// enter typing state
					// toggle typing flag
					// (on enter event) validate w/ regex, toggle flag
					// save the names to state
					break;
				}
				if (sel_idx >= PlayBtn::t1 && sel_idx <= PlayBtn::t3) {
					selected_time = sel_idx;
					break;
				}
				if (sel_idx == PlayBtn::play) {
					// cant start without both names, and selected time
					clear_mem();
					return 0;
				}
			}
		}
		clear_btns();
		color_hover();
		color_select(selected_time);
		update();
		draw();
	}


	// if play
	return 0;

	// if back
	return 1;
}
void MenuView::opts() {

}
void MenuView::leaderboard() {

}

void MenuView::update() {
	sf::Vector2i mouse_pos = sf::Mouse::getPosition(*_window);
	int mouseX = mouse_pos.x;
	int mouseY = mouse_pos.y;
	sf::RectangleShape* rect_but;
	sf::FloatRect rect_bounds;
	for (size_t i = 1; i < _drawables.size(); i++) {
		rect_but = (sf::RectangleShape*)_drawables[i];
		rect_bounds = rect_but->getGlobalBounds();
		if (i == PlayBtn::second_box || i == PlayBtn::label1 || i == PlayBtn::label2) continue;
		if (mouseX > rect_bounds.left && mouseX < rect_bounds.left + rect_bounds.width
			&& mouseY > rect_bounds.top && mouseY < rect_bounds.top + rect_bounds.height) {
			sel_idx = i;
			return;
		}
	}
	sel_idx = -1;
}

void MenuView::draw() {
	_window->clear(MenuColors::BACKGROUND);
	for (auto& piece : _pieces) {
		_window->draw(*piece);
	}
	for (auto& drawable : _drawables) {
		_window->draw(*drawable);
	}
	for (auto& text : _texts) {
		_window->draw(*text);
	}
	_window->display();
}