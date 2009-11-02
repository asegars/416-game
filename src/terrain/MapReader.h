/*
 * MapReader.h
 *
 *  Created on: Nov 1, 2009
 *      Author: luke
 */

#ifndef MAPREADER_H_
#define MAPREADER_H_

#include <string>
#include "WorldMap.h"

class MapReader {
public:
	MapReader();
	virtual ~MapReader();

	WorldMap* readMap(std::string filename);
	Terrain* getTileType(int mapVal);

private:
	WorldMap* map;
};

#endif /* MAPREADER_H_ */
