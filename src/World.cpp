/*
 * World.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */

#include "World.h"

World::World(std::string filename) {
	background = new Sprite(filename);
}

World::~World() {
	delete background;
}
