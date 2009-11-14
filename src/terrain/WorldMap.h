/*
 * WorldMap.h
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_

#include "Terrain.h"


class WorldMap {
public:
	WorldMap(int w, int h, int cd);
	virtual ~WorldMap();

	void setCell(int x, int y, Terrain* t) { map[y * cellWidth + x] = t; }
	Terrain* getCell(int x, int y) const { return map[y * cellWidth + x]; }
	Terrain* getCell(int loc) const { return map[loc]; }
	int locationToCell(float x, float y);
	int getCellDim() const { return cellDim; }
	int getCellWidth() const { return cellWidth; }
	int getCellHeight() const { return cellHeight; }
	Terrain** getMap() const { return map; }
private:
	int cellWidth, cellHeight, cellDim;
	Terrain** map;
};

#endif /* WORLDMAP_H_ */
