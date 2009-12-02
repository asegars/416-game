/*
 * GraphicManager.cpp
 *
 *  Created on: Nov 15, 2009
 *      Author: alsegars
 */

#include <SDL/SDL_image.h>
#include "GraphicManager.h"

GraphicManager* GraphicManager::manager = NULL;

GraphicManager::GraphicManager() {
	baseDir = "images/";
}

GraphicManager::~GraphicManager() {
	std::map<std::string, SDL_Surface*>::const_iterator iter = resources.begin();

	std::cout << "Freeing graphics." << std::endl;

	int index = 1;
	while (iter != resources.end()) {
		std::cout << "   Freeing " << iter->first << " [" << index++ << "/" << resources.size() << "]...";
		if (iter->second != NULL) {
			clear(iter->second);
		}
		std::cout << "done." << std::endl;
		iter++;
	}

	std::cout << "Graphics freed." << std::endl;
}

SDL_Surface* GraphicManager::read(std::string resName) {
	return SDL_LoadBMP((baseDir + resName).c_str());
//	return IMG_Load((baseDir + resName).c_str());
}

void GraphicManager::clear(SDL_Surface* resource) {
	SDL_FreeSurface(resource);
}
