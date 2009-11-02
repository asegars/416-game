/*
 * World.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */

#include <cmath>
#include <iostream>

#include "World.h"

World::World(std::string filename) {
	background = new Sprite(filename);

	int widthCells = ceil(static_cast<float>(background->getWidth()) / Terrain::getSize());
	int heightCells = ceil(static_cast<float>(background->getHeight()) / Terrain::getSize());
	std::cout << "World is composed of " << widthCells * heightCells << " cells." << std::endl;

	worldMap = NULL;
//	worldSurface = SDL_CreateRGBSurface(SDL_HWSURFACE | SDL_SRCALPHA, getWidth(), getHeight(), 32, 0, 200, 0, 0);
//	SDL_FillRect(worldSurface, NULL, SDL_MapRGBA(worldSurface->format, 0, 0, 0, 0));
}

World::~World() {
	if (background != NULL) delete background;
	if (worldMap != NULL) delete worldMap;

	if (worldSurface != NULL) SDL_FreeSurface(worldSurface);
}

void World::add(Terrain* t, int cellX, int cellY) {
	worldMap->setCell(cellX, cellY, t);
	int cellDim = worldMap->getCellDim();

	// Blit terrain onto the backgrounda single time.
	//   This means terrain can't (easily) go away, but it will greatly speed
	//   up redraws.
	SDL_Rect terrainBounds = {0, 0, 80, 80};
	SDL_Rect terrainPos = {cellX * cellDim, cellY * cellDim, 0, 0};
	SDL_BlitSurface(t->getSprite()->getSurface(), &terrainBounds, background->getSurface(), &terrainPos);
}

void World::setMap(WorldMap* map) {
	worldMap = map;
	SDL_Rect terrainBounds = {0, 0, 80, 80};

	int cellDim = worldMap->getCellDim();
	std::cout << "Blitting" << std::endl;
	// Blit the terrain onto the background surface.  This will only be performed
	//    once (directly onto the background) to improve screen redraw rate.
	for (int height = 0; height < worldMap->getCellHeight(); ++height) {
		for (int width = 0; width < worldMap->getCellWidth(); ++width) {
			SDL_Rect terrainPos = {width * cellDim, height * cellDim, 0, 0};
			// If the cell has terrain in it, blit it
			if (map->getCell(width, height) != NULL) {
				SDL_BlitSurface(map->getCell(width, height)->getSprite()->getSurface(),
						&terrainBounds,
						worldSurface,
						&terrainPos);
			}
		}
	}
	std::cout << "Done blitting." << std::endl;
}
