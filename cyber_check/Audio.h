#pragma once
#include<iostream>
#include<thread>
#include<queue>
#include<SFML/Audio.hpp>
enum class AudioEvent {
	Check,
	End,
	Hit,
	Place
};

class Audio {
	static std::queue<AudioEvent> _events;
public:
	AudioEvent audio_event;
	int play();
	bool event_poll();
	static void push_event(AudioEvent event);
};