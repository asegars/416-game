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
	terrain.resize(widthCells * heightCells);
	std::cout << "World is composed of " << widthCells * heightCells << " cells." << std::endl;
}

World::~World() {
	delete background;
}
