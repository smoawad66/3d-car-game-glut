#include <SoundEngine.h>

using namespace std;

SoundEngine::SoundEngine(const string& soundsPath) {
    this->soundsPath = soundsPath;
}

SoundEngine::~SoundEngine() {
    cleanupAudio();
}

void SoundEngine::initAudio() {
    if (SDL_InitSubSystem(SDL_INIT_AUDIO) < 0) {
        cout << "Audio subsystem failed: " << SDL_GetError() << endl;
        return;
    }
    
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        cout << "SDL_mixer failed: " << Mix_GetError() << endl;
        return;
    }
}


void SoundEngine::playSound(const string& filename) {
	string fullPath = soundsPath + filename;
    if (soundCache.find(filename) == soundCache.end()) {
        Mix_Chunk* sound = Mix_LoadWAV(fullPath.c_str());
        if (sound) {
            soundCache[filename] = sound;
        } else {
            cout << "Failed to load sound: " << filename << " Error: " << Mix_GetError() << endl;
            return;
        }
    }
    
    Mix_PlayChannel(-1, soundCache[filename], 0);
}

void SoundEngine::cleanupAudio() {
    for (auto& pair : soundCache) {
        Mix_FreeChunk(pair.second);
    }
    soundCache.clear();
    Mix_CloseAudio();
    SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

