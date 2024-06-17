#pragma once
#include<iostream>
#include<thread>
#include<queue>
#include<SFML/Audio.hpp>
enum class AudioEvent {
	Check,
	Hit,
	Place,
	Click,
	Terminate,
};

class Audio {
	static std::queue<AudioEvent> _events;

public:
	static int effects_volume;
	static int music_volume;
	AudioEvent audio_event;
	int play();
	bool event_poll();
	static void push_event(AudioEvent event);

	
};