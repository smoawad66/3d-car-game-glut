#ifndef SOUND_ENGINE_H
#define SOUND_ENGINE_H

#include <iostream>
#include <string>
#include <map>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL.h>
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

#endif