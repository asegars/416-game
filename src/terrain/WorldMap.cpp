/*
 * WorldMap.cpp
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */

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
	if (map != NULL) delete map;
}
