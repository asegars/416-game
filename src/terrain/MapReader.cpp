/*
 * MapReader.cpp
 *
 *  Created on: Nov 1, 2009
 */
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Terrain.h"
#include "SolidTerrain.h"
#include "../Manager.h"
#include "MapReader.h"
#include "WorldMap.h"

MapReader::MapReader() {

}

MapReader::~MapReader() {
}

Terrain* MapReader::getTileType(int mapVal) {
	Terrain* newTerrain = NULL;

	if (mapVal == 1) {
		newTerrain = new SolidTerrain();
	}

	return newTerrain;
}

WorldMap* MapReader::readMap(std::string filename) {
	std::ifstream infile(filename.c_str());
	int cellWidth = 0;
	int cellHeight = 0;
	int nextTileVal = 0;
	std::stringstream lineStream;

	infile >> cellWidth >> cellHeight;
	WorldMap* map = new WorldMap(cellWidth, cellHeight, Terrain::getSize());

	std::cout << "Loading map [" << filename << "]   (" << cellWidth << ", " << cellHeight << ")" << std::endl;

	// Loop through each row of the map
	for (int height = 0; height < cellHeight; ++height) {
		// Loop through each column of the map
		for (int width = 0; width < cellWidth; ++width) {
			infile >> nextTileVal;

			// Special case -- victory condition
			if (nextTileVal == 2) {
				Manager::getInstance()->getTarget()->setLocation(width * Terrain::getSize(), height * Terrain::getSize());
			}
			// All other cases.
			else {
				Terrain * nextTileType = getTileType(nextTileVal);
				if (nextTileType != NULL) {
					map->setCell(width, height, nextTileType);
				}
			}
		}
		lineStream.str("");
	}

	/*
	for (int width = 0; width < cellWidth; ++width) {
		map->setCell(width, cellHeight - 1, getTileType(1));
	}
	*/

	return map;
}
