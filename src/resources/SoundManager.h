/*
 * SoundManager.h
 *
 *  Created on: Nov 9, 2009
 *      Author: luke
 */

#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <string>
#include <SDL/SDL_mixer.h>
#include "ResourceManager.h"

class SoundManager : public ResourceManager<Mix_Chunk *> {
public:
	static SoundManager* getInstance() {
		if (manager == NULL) {
			manager = new SoundManager();
		}

		return manager;
	}
	virtual ~SoundManager();

	void play(Mix_Chunk* music);
	void play(Mix_Chunk* music, int repeats);
	void stop();

protected:
	SoundManager();

	Mix_Chunk* read(std::string resName);
	virtual void clear(Mix_Chunk* resource);

private:
	static SoundManager* manager;
};

#endif /* SOUNDMANAGER_H_ */
