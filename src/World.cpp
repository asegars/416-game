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

	worldMap = new WorldMap(widthCells, heightCells, Terrain::getSize());
}

World::~World() {
	if (background != NULL) delete background;
	if (worldMap != NULL) delete worldMap;
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
