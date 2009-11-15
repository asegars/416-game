/*
 * GraphicManager.h
 *
 *  Created on: Nov 15, 2009
 *      Author: alsegars
 */

#ifndef GRAPHICMANAGER_H_
#define GRAPHICMANAGER_H_

#include <SDL/SDL.h>
#include "ResourceManager.h"

class GraphicManager : public ResourceManager<SDL_Surface *> {
public:
	static GraphicManager* getInstance() {
		if (manager == NULL) {
			manager = new GraphicManager();
		}
		return manager;
	}
	virtual ~GraphicManager();

protected:
	GraphicManager();
	virtual SDL_Surface* read(std::string resName);
	virtual void clear(SDL_Surface* resource);

	static GraphicManager* manager;
};

#endif /* GRAPHICMANAGER_H_ */
