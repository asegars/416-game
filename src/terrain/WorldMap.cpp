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

	arrayMap = new Terrain*[cellHeight * cellWidth];
	for (int i = 0; i < cellHeight * cellWidth; ++i) {
		arrayMap[i] = NULL;
	}
}

WorldMap::~WorldMap() {
	std::list<Terrain *>::iterator iter;

	for (iter = terrainMap.begin(); iter != terrainMap.end(); ++iter) {
		delete *iter;
	}

	terrainMap.clear();
	delete arrayMap;
}


void WorldMap::setCell(int x, int y, Terrain* t) {
	t->setLocation(x * cellDim, y * cellDim);

	arrayMap[y * cellWidth + x] = t;
	terrainMap.push_back(t);
}

int WorldMap::locationToCell(float x, float y) {
//	int xCell = ceil(x / cellDim);
//	int yCell = ceil(y / cellDim);
	int xCell = floor(x / cellDim);
	int yCell = floor(y / cellDim);

	return yCell * cellWidth + xCell;
}
