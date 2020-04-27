#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "SDL.h"
#include "EngineStructs.h"
#include "Logger.h"

/*!
	The Audio Manager is a singleton that allows the playing of WAV files. The AudioManager relies on the AudioPack to function.
	\warning This Audio Manager will ONLY play WAV files. Do not try other file types. You will void your warranty.
*/
class AudioManager
{
private:
	static AudioManager* sInstance; /*!< Static instance of the AudioManager class. */

	std::unordered_map<std::string, AudioPack> audioHashMap; /*!< A hashmap for efficient storage of the AudioPacks.*/

public:

	/*!
		An easy-to-use function that plays an audio file instantly.
		\param[in] filePath The filePath of the audio file to be played.
	*/
	bool PlayAudio(std::string filePath);

	/*!
		Method for getting an instance of AudioManager.
	*/
	static AudioManager* Instance();

private:
	/*!
		A QoL function that checks if the audioHashMap has a certain key.
		\param[in] key The key to search for
		\return Whether or not the key was found in the audioHashMap.
	*/
	bool CheckHashMap(std::string key);

	AudioManager();
	~AudioManager();
};