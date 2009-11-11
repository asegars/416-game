/*
 * SoundManager.h
 *
 *  Created on: Nov 9, 2009
 *      Author: luke
 */

#ifndef SOUNDMANAGER_H_
#define SOUNDMANAGER_H_

#include <string>
#include "ResourceManager.h"

class SoundManager : public ResourceManager<Mix_Music *> {
public:
	SoundManager();
	virtual ~SoundManager();

	void play(Mix_Music* music, int repeats);
	void stop();

protected:
	Mix_Music* read(std::string resName);
};

#endif /* SOUNDMANAGER_H_ */
