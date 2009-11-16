/*
 * WorldMap.h
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */

#ifndef WORLDMAP_H_
#define WORLDMAP_H_

#include <list>
#include "Terrain.h"


class WorldMap {
public:
	WorldMap(int w, int h, int cd);
	virtual ~WorldMap();

	void setCell(int x, int y, Terrain* t);
	int locationToCell(float x, float y);
	int getCellDim() const { return cellDim; }
	int getCellWidth() const { return cellWidth; }
	int getCellHeight() const { return cellHeight; }
	std::list<Terrain*> getMap() const { return terrainMap; }
	Terrain** getMapArray() { return arrayMap; }
private:
	int cellWidth, cellHeight, cellDim;
	std::list<Terrain*> terrainMap;
	Terrain** arrayMap;
};

#endif /* WORLDMAP_H_ */
