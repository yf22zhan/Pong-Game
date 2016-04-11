#pragma once
#include "IAudioProvider.h"

class ServiceLocator
{
public:
	static IAudioProvider* getAudio() { return _audioProvider; } const

		static void registerServiceLocator(IAudioProvider *provider)
	{
		_audioProvider = provider;
	}

private:
	static IAudioProvider * _audioProvider;
};