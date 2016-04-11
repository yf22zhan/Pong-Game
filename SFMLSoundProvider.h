#pragma once

#include "IAudioProvider.h"
#include "SoundFileCache.h"
#include "SFML/Audio.hpp"

class SFMLSoundProvider : public IAudioProvider
{
public:
	SFMLSoundProvider();

	void playSound(std::string filename);
	void playSong(std::string filename, bool looping = false);
	void stopAllSounds();

	bool isSoundPlaying();
	bool isSongPlaying();

private:
	static const int MAX_SOUND_CHANNELS = 5;

	SoundFileCache _soundFileCache;
	sf::Sound   _currentSounds[MAX_SOUND_CHANNELS];
	std::string _currentSongName;
};