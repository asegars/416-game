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
	int cellWidth, cellHeight;
	int nextTileVal;
	std::stringstream lineStream;

	infile >> cellWidth >> cellHeight;
	WorldMap* map = new WorldMap(cellWidth, cellHeight, Terrain::getSize());

	std::cout << "Loading map [" << filename << "]   (" << cellWidth << ", " << cellHeight << ")" << std::endl;

	// Loop through each row of the map
	for (int height = 0; height < cellHeight; ++height) {
		// Loop through each column of the map
		for (int width = 0; width < cellWidth; ++width) {
			infile >> nextTileVal;
			map->setCell(width, height, getTileType(nextTileVal));
		}
		lineStream.str("");
	}

	return map;
}
