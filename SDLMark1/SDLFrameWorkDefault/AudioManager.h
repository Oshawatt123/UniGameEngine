#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "SDL.h"
#include "EngineStructs.h"
#include "Logger.h"

class AudioManager
{
private:
	static AudioManager* sInstance;

	std::unordered_map<std::string, AudioPack> audioHashMap;

public:
	bool PlayAudio(std::string filePath);

	static AudioManager* Instance();

private:
	bool CheckHashMap(std::string key);

	AudioManager();
	~AudioManager();
};