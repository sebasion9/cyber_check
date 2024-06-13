#include"Audio.h"
std::queue<AudioEvent> Audio::_events;

int Audio::play() {
	sf::Music main_theme;
	sf::SoundBuffer hit_buffer;
	sf::SoundBuffer place_buffer;
	sf::SoundBuffer check_buffer;
	sf::Sound hit;
	sf::Sound place;
	sf::Sound check;
	if (!hit_buffer.loadFromFile("assets/hit.mp3")) {
		return -1;
	}
	if (!place_buffer.loadFromFile("assets/place.mp3")) {
		return -1;
	}
	if (!check_buffer.loadFromFile("assets/check.wav")) {
		return -1;
	}
	if (!main_theme.openFromFile("assets/main_theme.mp3")) {
		return -1;
	}
	main_theme.setVolume(5.0f);
	hit.setBuffer(hit_buffer);
	hit.setVolume(30.0f);
	place.setBuffer(place_buffer);
	place.setVolume(30.0f);
	check.setBuffer(check_buffer);
	check.setVolume(30.0f);
	std::thread event_t;;
	while (true) {
		if (event_poll()) {
			switch (audio_event) {
				case AudioEvent::Check:
					event_t = std::thread(&sf::Sound::play, &check);
					event_t.join();
					break;
				case AudioEvent::Place:
					event_t = std::thread(&sf::Sound::play, &place);
					event_t.join();
					break;
				case AudioEvent::Hit:
					event_t = std::thread(&sf::Sound::play, &hit);
					event_t.join();
					break;
				case AudioEvent::End:
					break;
				default:
					break;
			}
		}
		if (main_theme.getStatus() != sf::Music::Playing) {
			main_theme.play();
		}
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