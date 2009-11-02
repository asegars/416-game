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

	static WorldMap* readMap(std::string filename);

private:
	static Terrain* getTileType(int mapVal);
};

#endif /* MAPREADER_H_ */
