#include"Audio.h"
std::queue<AudioEvent> Audio::_events;
int Audio::effects_volume = 50;
int Audio::music_volume = 50;
int Audio::play() {
	bool terminate = false;
	sf::Music main_theme;
	sf::SoundBuffer hit_buffer;
	sf::SoundBuffer place_buffer;
	sf::SoundBuffer check_buffer;
	sf::SoundBuffer click_buffer;
	sf::Sound hit;
	sf::Sound place;
	sf::Sound check;
	sf::Sound click;
	if (!hit_buffer.loadFromFile("assets/hit.mp3")) {
		return -1;
	}
	if (!place_buffer.loadFromFile("assets/place.mp3")) {
		return -1;
	}
	if (!check_buffer.loadFromFile("assets/check.wav")) {
		return -1;
	}
	if (!click_buffer.loadFromFile("assets/click.wav")) {
		return -1;
	}
	if (!main_theme.openFromFile("assets/main_theme.mp3")) {
		return -1;
	}
	main_theme.setVolume(music_volume);
	hit.setBuffer(hit_buffer);
	hit.setVolume(effects_volume);
	place.setBuffer(place_buffer);
	place.setVolume(effects_volume);
	check.setBuffer(check_buffer);
	check.setVolume(effects_volume);
	click.setBuffer(click_buffer);
	click.setVolume(effects_volume);
	while (true) {
		if (event_poll()) {
			switch (audio_event) {
				case AudioEvent::Check:
					check.play();
					break;
				case AudioEvent::Place:
					place.play();
					break;
				case AudioEvent::Hit:
					hit.play();
					break;
				case AudioEvent::Click:
					click.play();
					break;
				case AudioEvent::Terminate:
					terminate = true;
					break;
				default:
					break;
			}
		}
		if (main_theme.getStatus() != sf::Music::Playing) {
			main_theme.play();
		}
		if (terminate) {
			return 0;
		}
		main_theme.setVolume(music_volume);
		hit.setVolume(effects_volume);
		place.setVolume(effects_volume);
		check.setVolume(effects_volume);
		click.setVolume(effects_volume);
	}
	

	return 1;
}


bool Audio::event_poll() {
	if (_events.size() < 1) {
		return false;
	}
	audio_event = _events.front();
	_events.pop();
	return true;
}

void Audio::push_event(AudioEvent event) {
	_events.push(event);
}