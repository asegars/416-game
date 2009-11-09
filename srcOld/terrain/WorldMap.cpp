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

	map = new Terrain*[cellHeight * cellWidth];
	for (int i = 0; i < cellHeight * cellWidth; ++i) {
		map[i] = NULL;
	}
}

WorldMap::~WorldMap() {
	for (int i = 0; i < cellHeight * cellWidth; ++i) {
		delete map[i];
	}
	if (map != NULL) delete [] map;
}

int WorldMap::locationToCell(float x, float y) {
	int xCell = floor(x / cellDim);
	int yCell = floor(y / cellDim);

	return yCell * cellWidth + xCell;
}