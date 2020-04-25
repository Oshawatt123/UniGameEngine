#include "AudioManager.h"

AudioManager* AudioManager::sInstance = NULL;

bool AudioManager::PlayAudio(std::string filePath)
{
	// check if we have loaded the audio already
	if (!CheckHashMap(filePath))
	{
		Log("Loading new audio file", DEBUG);
		// load audio for first time
		AudioPack newAudioPack;
		SDL_LoadWAV(filePath.c_str(), &newAudioPack.wavSpec,
			&newAudioPack.wavBuffer, &newAudioPack.wavLength);

		newAudioPack.devideID = SDL_OpenAudioDevice(NULL, 0, &newAudioPack.wavSpec, NULL, 0);

		audioHashMap.insert(std::make_pair(filePath, newAudioPack));
	}

	// play the audio file
	AudioPack inUseAudioPack = audioHashMap[filePath];
	// queue audio
	SDL_QueueAudio(inUseAudioPack.devideID, inUseAudioPack.wavBuffer, inUseAudioPack.wavLength);
	// pause audio
	SDL_PauseAudioDevice(inUseAudioPack.devideID, 0);
	Log("Playing audio file", DEBUG);
	return false;
}

AudioManager* AudioManager::Instance()
{
	if (sInstance == NULL)
	{
		sInstance = new AudioManager();
	}
	return sInstance;
}

bool AudioManager::CheckHashMap(std::string key)
{
	if (audioHashMap.find(key) == audioHashMap.end()) return false;
	return true;
}

AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
	for (auto& x : audioHashMap)
	{
		// X->first is the key

		// X->second is the value
		SDL_CloseAudioDevice(x.second.devideID);
		SDL_FreeWAV(x.second.wavBuffer);
	}
}
