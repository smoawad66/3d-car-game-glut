#pragma once
#include <string>
#include <map>
#include <SDL2/SDL_mixer.h>
using namespace std;

class SoundEngine
{

public:
    string soundsPath;
    map<string, Mix_Chunk*> soundCache;

	SoundEngine(const string& soundsPath);
	~SoundEngine();
	
	void initAudio();
	void playSound(const string& filename);
	void cleanupAudio();
};