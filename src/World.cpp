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

//	int widthCells = ceil(static_cast<float>(background->getWidth()) / Terrain::getSize());
//	int heightCells = ceil(static_cast<float>(background->getHeight()) / Terrain::getSize());
//	std::cout << "World is composed of " << widthCells * heightCells << " cells." << std::endl;

	worldMap = NULL;
}

World::~World() {
	if (background != NULL) delete background;
	if (worldMap != NULL) delete worldMap;
}

void World::add(Terrain* t, int cellX, int cellY) {
	worldMap->setCell(cellX, cellY, t);
}

void World::setMap(WorldMap* map) {
	worldMap = map;
}
