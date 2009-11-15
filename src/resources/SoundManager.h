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

class SoundManager : public ResourceManager<Mix_Music *> {
public:
	static SoundManager* getInstance() {
		if (manager == NULL) {
			manager = new SoundManager();
		}

		return manager;
	}
	virtual ~SoundManager();

	void play(Mix_Music* music);
	void play(Mix_Music* music, int repeats);
	void stop();

protected:
	SoundManager();

	Mix_Music* read(std::string resName);
	virtual void clear(Mix_Music* resource);

private:
	static SoundManager* manager;
};

#endif /* SOUNDMANAGER_H_ */
