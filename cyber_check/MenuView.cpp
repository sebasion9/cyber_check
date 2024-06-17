#include"MenuView.h"
#include <filesystem>
#include <filesystem>

MenuView::MenuView() {
}

MenuView::MenuView(sf::RenderWindow* win, const std::string &font_path) {
	if (!font.loadFromFile(font_path)) {
		std::cerr << "couldnt load font, exiting now";
		exit(1);
	}
	sel_idx = -1;
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

bool MenuView::endgame() {
	clear_mem();
	menu_box();
	auto win_size = _window->getSize();
	auto w = win_size.x / 4.0f;
	auto h = win_size.y * 4.0f / 5.0f;
	auto x = 1.5 * w;
	auto y = win_size.y / 6.0f;

	auto play_again = init_rect(0);
	auto ldb = init_rect(1);
	auto main_menu = init_rect(2);
	init_text("play again", play_again);
	init_text("leaderboard", ldb);
	init_text("main menu", main_menu);


	std::string res_string;
	auto winner = State::get_player(State::whosturn());
	
	State::_draw ? res_string = "DRAW" : res_string = winner->get_name() + " WON";
	auto title_color = MenuColors::TEXT_PRIMARY;
	sf::Text* result = new sf::Text;
	result->setFont(font);
	result->setFillColor(MenuColors::TEXT_PRIMARY);
	result->setString(res_string);
	result->setScale(1.5f, 1.5f);
	sf::FloatRect gt_rect = result->getLocalBounds();
	result->setOrigin(gt_rect.left + gt_rect.width / 2.0f,
		gt_rect.top + gt_rect.height / 2.0f);
	result->setPosition(vec2f(x + w / 2.0f, y + h / 10.0f));
	_texts.push_back(result);

	auto players = State::get_player();
	if (State::_draw) {
		update_ldb(players.first->get_name(), 2);
		_ldb = update_ldb(players.second->get_name(), 2);
	}
	else {
		if (State::whosturn()) {
			update_ldb(players.first->get_name(), 0);
			_ldb = update_ldb(players.second->get_name(), 1);
		}
		else {
			update_ldb(players.first->get_name(), 1);
			_ldb = update_ldb(players.second->get_name(), 0);
		}
	}
	sf::Event event;
	for (;;) {
		while (_window->pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				click_sound();
				if (sel_idx == EndgameBtn::play_again) {
					clear_mem();
					if (!play_menu()) {
						return 1;
					}
					continue;
				}
				if (sel_idx == EndgameBtn::leaderboard) {
					clear_mem();
					leaderboard();
					return 0;
				}
				if (sel_idx == EndgameBtn::menu) {
					clear_mem();
					return 0;
				}
			}
		}

		update();
		draw();
	}
}

int MenuView::loop() {
	sf::Clock clock;
	int frame_count = 0;
	float frame_time = 0;
	sel_idx = -1;
	_ldb = open_ldb();
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
				click_sound();
				if (sel_idx == 1) {
					if (!play_menu()) {
						return 0;
					}
					main_menu();
					break;
				}
				if (sel_idx == 2) {
					opts();
					main_menu();
					break;
				}
				if (sel_idx == 3) {
					leaderboard();
					main_menu();
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
		draw();
		update();
	}
	return 0;
}
void MenuView::color_hover() {
	if (sel_idx != -1 && sel_idx < _drawables.size()) {
		sf::RectangleShape* button = (sf::RectangleShape*)_drawables[sel_idx];
		button->setFillColor(MenuColors::HOVER);
	}
}
void MenuView::color_select(int selected) {
	if (selected != -1 && selected < _drawables.size()) {
		sf::RectangleShape* button = (sf::RectangleShape*)_drawables[selected];
		button->setFillColor(MenuColors::SELECT);
	}
}
void MenuView::click_sound() {
	Audio::push_event(AudioEvent::Click);
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


	int selected_time = -1;
	int selected_input = -1;
	bool is_typing = false;
	std::string name1 = "";
	std::string name2 = "";
	sf::Text* name1_text = _texts[PlayText::name1];
	sf::Text* name2_text = _texts[PlayText::name2];

	name1_text->setFillColor(MenuColors::PRIMARY);
	name2_text->setFillColor(MenuColors::PRIMARY);

	sf::Event event;
	bool res1 = false;
	bool res2 = false;
	for (;;) {
		while (_window->pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				click_sound();
				if (sel_idx == PlayBtn::back) {
					is_typing = false;
					clear_mem();
					return 1;
				}
				if (sel_idx == PlayBtn::input1 || sel_idx == PlayBtn::input2) {
					selected_input = sel_idx;
					is_typing = true;
					continue;
				}
				if (sel_idx >= PlayBtn::t1 && sel_idx <= PlayBtn::t3) {
					is_typing = false;
					selected_time = sel_idx;
					continue;
				}
				if (sel_idx == PlayBtn::play) {
					is_typing = false;
					if (res1 && res2 && selected_time != -1) {
						clear_mem();
						int time = 600000;
						auto players = State::get_player();
						if (selected_time == PlayBtn::t1) time = 180000;
						if (selected_time == PlayBtn::t2) time = 300000;
						players.first->set_name(name2);
						players.second->set_name(name1);
						players.first->set_time(time);
						players.second->set_time(time);
						return 0;
					}
					
				}
			}
			if (event.type == sf::Event::TextEntered) {
				char ch = (char)event.text.unicode;
				if (is_typing && (
					(ch <= 'Z' && ch >= 'A')
					||
					(ch <= 'z' && ch >= 'A')
					||
					ch == '_'
					)) {
					if (selected_input == PlayBtn::input1) {
						name1 += ch;
						continue;
					}
					if (selected_input == PlayBtn::input2) {
						name2 += ch;
						continue;
					}
				}
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Backspace && is_typing) {
					if (selected_input == PlayBtn::input1 && !name1.empty()) {
						name1.pop_back();
						continue;
					}
					if (selected_input == PlayBtn::input2 && !name2.empty()) {
						name2.pop_back();
						continue;
					}
				}
			}
		}
		auto username_expr = std::regex("^[a-zA-Z](\\w){1,9}$");
		res1= std::regex_match(name1, username_expr);
		res2= std::regex_match(name2, username_expr);
		!res1 ? name1_text->setFillColor(MenuColors::TEXT_NOK) : name1_text->setFillColor(MenuColors::TEXT_OK);
		!res2 ? name2_text->setFillColor(MenuColors::TEXT_NOK) : name2_text->setFillColor(MenuColors::TEXT_OK);

		!name1.empty() ? name1_text->setString(name1) : name1_text->setString("white...");
		!name2.empty() ? name2_text->setString(name2) : name2_text->setString("black...");

		update();
		draw();
		color_select(selected_time);
	}
}
void MenuView::opts() {
	clear_mem();
	menu_box();
	sel_idx = -1;
	auto win_size = _window->getSize();
	auto w = win_size.x / 4.0f;
	auto h = win_size.y * 4.0f / 5.0f;
	auto x = 1.5 * w;
	auto y = win_size.y / 6.0f;
	sf::RectangleShape* box = new sf::RectangleShape(vec2f(w, h / 2));
	auto gt_rect = box->getLocalBounds();
	box->setFillColor(MenuColors::PRIMARY);
	box->setPosition(vec2f(x, y));


	auto music_p = init_rect(0, box->getGlobalBounds());
	auto music_n = init_rect(1, box->getGlobalBounds());
	auto effects_p = init_rect(2, box->getGlobalBounds());
	auto effects_n = init_rect(3, box->getGlobalBounds());
	init_rect(6, box->getGlobalBounds());
	init_rect(6, box->getGlobalBounds());
	init_rect(6, box->getGlobalBounds());
	auto volume = init_rect(6, box->getGlobalBounds());
	auto back = init_rect(7, box->getGlobalBounds());
	init_text("music+", music_p);
	init_text("music-", music_n);
	init_text("effects+", effects_p);
	init_text("effects-", effects_n);
	init_text("+++++++++", volume);
	init_text("back", back);
	bool is_music = false;
	auto vol_text = _texts[4];
	std::string vol_level = "+++++";
	sf::Event event;
	for (;;) {
		while (_window->pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				click_sound();
				if (sel_idx == OptsBtn::music_p && Audio::music_volume < 100) {
					is_music = true;
					Audio::music_volume += 10;
					continue;
				}
				if (sel_idx == OptsBtn::music_n && Audio::music_volume > 0) {
					is_music = true;
					Audio::music_volume -= 10;
					continue;
				}
				if (sel_idx == OptsBtn::effects_p && Audio::effects_volume < 100) {
					is_music = false;
					Audio::effects_volume += 10;
					continue;
				}
				if (sel_idx == OptsBtn::effects_n && Audio::effects_volume > 0) {
					is_music = false;
					Audio::effects_volume -= 10;
					continue;
				}
				if (sel_idx == OptsBtn::back) {
					clear_mem();
					return;
				}
			}
		}
		is_music ? vol_level = std::string(Audio::music_volume / 10, '+') : vol_level = std::string(Audio::effects_volume / 10, '+');
		vol_text->setString(vol_level);
		update();
		draw();
	}

}
void MenuView::leaderboard() {
	clear_mem();
	menu_box();
	auto box = (sf::RectangleShape*)_drawables[0];
	auto hidden_box = box->getGlobalBounds();
	hidden_box.top -= box->getGlobalBounds().top;

	std::string entry;
	entry += "name w/l/d";
	init_text(entry, hidden_box);
	for (size_t i = 0; i < 10; i++) {
		if (i < _ldb.size()) {
			hidden_box.top += _texts[0]->getCharacterSize();
			entry = _ldb[i].name + " " + std::to_string(_ldb[i].wins) + "/" + std::to_string(_ldb[i].loses) + "/" + std::to_string(_ldb[i].draws);
			init_text(entry, hidden_box);
		}
	}
	auto back = init_rect(3);
	init_text("back", back);
	sf::Event event;
	for (;;) {
		while (_window->pollEvent(event)) {
			if (event.type == sf::Event::MouseButtonPressed) {
				click_sound();
				if (sel_idx == 1) {
					clear_mem();
					return;
				}
			}
		}
		update();
		draw();
	}
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

	auto draw_item = [this](auto& item) {
		_window->draw(*item);
	};

	std::ranges::for_each(_pieces, draw_item);
	std::ranges::for_each(_drawables, draw_item);
	std::ranges::for_each(_texts, draw_item);

	clear_btns();
	color_hover();
	_window->display();
}

std::vector<ldb_entry> MenuView::update_ldb(const std::string& pname, int stat) {
	std::vector<ldb_entry> res;

	auto path = fs::path(fs::current_path() / LEADERBOARD_PATH);
	if (!fs::exists(path)) {
		fs::create_directories(path.parent_path());
		std::ofstream ofs(path);
		if (stat == 0) {
			ofs << pname << " 1 0 0\n";
		}
		else if (stat == 1) {
			ofs << pname << " 0 1 0\n";
		}
		else {
			ofs << pname << " 0 0 1\n";
		}
		ofs.close();
		res.push_back({ pname, stat == 0 ? 1 : 0, stat == 1 ? 1 : 0, stat == 2 ? 1 : 0 });
	}
	else {
		std::ifstream ifs(path);
		std::vector<ldb_entry> leaderboard;
		std::string line;
		bool player_found = false;

		while (std::getline(ifs, line)) {
			std::istringstream iss(line);
			std::string name;
			int wins, loses, draws;

			if (!(iss >> name >> wins >> loses >> draws)) {
				std::cerr << "error parsing line: " << line << std::endl;
				continue;
			}

			if (name == pname) {
				player_found = true;
				if (stat == 0) {
					wins++;
				}
				else if (stat == 1) {
					loses++;
				}
				else {
					draws++;
				}
			}

			leaderboard.push_back({ name, wins, loses, draws });
		}
		ifs.close();

		if (!player_found) {
			if (stat == 0) {
				leaderboard.push_back({ pname, 1, 0, 0 });
			}
			else if (stat == 1) {
				leaderboard.push_back({ pname, 0, 1, 0 });
			}
			else {
				leaderboard.push_back({ pname, 0, 0, 1 });
			}
		}
		std::ofstream ofs(path);
		auto push_entry = [&res, &ofs](ldb_entry &entry) {
			ofs << entry.name << " " << entry.wins << " " << entry.loses << " " << entry.draws << "\n";
			res.push_back(entry);
		};
		std::ranges::for_each(leaderboard, push_entry);
		ofs.close();
	}

	return res;
}


std::vector<ldb_entry> MenuView::open_ldb() {
	std::vector<ldb_entry> leaderboard;

	auto path = fs::path(fs::current_path() / LEADERBOARD_PATH);
	if (!fs::exists(path)) {
		fs::create_directories(path.parent_path());
		std::ofstream ofs(path);
		return leaderboard;
	}
	else {
		std::ifstream ifs(path);
		std::vector<ldb_entry> leaderboard;
		std::string line;
		bool player_found = false;

		while (std::getline(ifs, line)) {
			std::istringstream iss(line);
			std::string name;
			int wins, loses, draws;

			if (!(iss >> name >> wins >> loses >> draws)) {
				std::cerr << "error parsing line: " << line << std::endl;
				continue;
			}

			leaderboard.push_back({ name, wins, loses, draws });
		}
		ifs.close();
		return leaderboard;
	}
}