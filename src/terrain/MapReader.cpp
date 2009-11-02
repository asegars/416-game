/*
 * MapReader.cpp
 *
 *  Created on: Nov 1, 2009
 *      Author: luke
 */
#include <string>
#include <fstream>
#include <sstream>
#include "Terrain.h"
#include "SolidTerrain.h"
#include "MapReader.h"
#include "WorldMap.h"

MapReader::MapReader() {
	// TODO Auto-generated constructor stub

}

MapReader::~MapReader() {
	// TODO Auto-generated destructor stub
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
	char mapline[4096];
	int nextTileVal;
	std::stringstream lineStream;

	infile >> cellWidth >> cellHeight;
	map = new WorldMap(cellWidth, cellHeight, Terrain::getSize());

	for (int height = 0; height < cellHeight; ++height) {
		infile.getline(mapline, 4096);
		lineStream.str(mapline);
		for (int width = 0; width < cellWidth; ++width) {
			lineStream >> nextTileVal;
			map->setCell(width, height, getTileType(nextTileVal));
		}
		lineStream.str("");
	}
}
