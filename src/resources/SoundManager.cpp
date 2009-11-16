/*
 * SoundManager.cpp
 *
 *  Created on: Nov 9, 2009
 *      Author: luke
 */

#include <SDL/SDL_mixer.h>
#include "SoundManager.h"

SoundManager* SoundManager::manager = NULL;

SoundManager::SoundManager() {
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, AUDIO_S16SYS, 2, 4096);
	Mix_AllocateChannels(8);
	baseDir = "music/";
}

SoundManager::~SoundManager() {
	std::map<std::string, Mix_Chunk *>::const_iterator iter = resources.begin();

	std::cout << "Freeing music." << std::endl;

	int index = 1;
	while (iter != resources.end()) {
		std::cout << "   Freeing " << iter->first << " [" << index++ << "/" << resources.size() << "]...";
		if (iter->second != NULL) {
			clear(iter->second);
		}
		std::cout << "done." << std::endl;
		iter++;
	}

	Mix_CloseAudio();
	std::cout << "Music freed." << std::endl;
}

Mix_Chunk* SoundManager::read(std::string resName) {
	return Mix_LoadWAV((baseDir + resName).c_str());
}

void SoundManager::play(Mix_Chunk* music) {
	play(music, -1);
}

void SoundManager::play(Mix_Chunk* music, int repeats) {
	Mix_PlayChannel(-1, music, repeats);
}

void SoundManager::stop() {
	Mix_HaltMusic();
}

void SoundManager::clear(Mix_Chunk* resource) {
	Mix_FreeChunk(resource);
}
