/*
 * World.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */

#include "World.h"

World::World(std::string filename) {
	background = new Sprite(filename, 0, 0);
}

World::~World() {
	delete background;
}
