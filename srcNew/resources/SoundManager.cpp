/*
 * SoundManager.cpp
 *
 *  Created on: Nov 9, 2009
 *      Author: luke
 */

#include <SDL/SDL_mixer.h>
#include "SoundManager.h"

SoundManager::SoundManager() {
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 256);

	baseDir = "music/";
}

SoundManager::~SoundManager() {
	Mix_CloseAudio();
}

Mix_Music* SoundManager::read(std::string resName) {
	return Mix_LoadMUS(resName.c_str());
}

void SoundManager::play(Mix_Music* music, int repeats = -1) {
	Mix_PlayMusic(music, repeats);
}

void SoundManager::stop() {
	Mix_HaltMusic();
}
