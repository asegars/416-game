/*
 * WorldMap.cpp
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */
#include <cmath>
#include <iostream>
#include "WorldMap.h"

WorldMap::WorldMap(int w, int h, int cd) {
	cellWidth = w;
	cellHeight = h;
	cellDim = cd;

//	map = new Terrain*[cellHeight * cellWidth];
//	for (int i = 0; i < cellHeight * cellWidth; ++i) {
//		map[i] = NULL;
//	}
}

WorldMap::~WorldMap() {
	for (unsigned int i = 0; i < terrainMap.size(); ++i) {
		if (terrainMap[i] != NULL) delete terrainMap[i];
	}
}


void WorldMap::setCell(int x, int y, Terrain* t) {
	t->setLocation(x * cellDim, y * cellDim);

	terrainMap.push_back(t);
}

int WorldMap::locationToCell(float x, float y) {
	int xCell = floor(x / cellDim);
	int yCell = floor(y / cellDim);

	return yCell * cellWidth + xCell;
}
