/*
 * World.cpp
 *
 *  Created on: Oct 6, 2009
*/

#include <cmath>
#include <iostream>

#include "Enemy.h"
#include "Player.h"
#include "World.h"

World::World(std::string filename) {
	background = new Sprite(filename);

	worldMap = NULL;
}

World::~World() {
	if (background != NULL) delete background;
	if (worldMap != NULL) delete worldMap;
}

void World::add(Terrain* t, int cellX, int cellY) {
	worldMap->setCell(cellX, cellY, t);
}

void World::setMap(WorldMap* map) {
	worldMap = map;
}

void World::assignPlayer(Player* p) {
	// TODO: Check if player is null...if so, search through the
	//   drawables list and remove the old player from that list
	//   before overwriting the pointer.
	player = p;
	drawables.push_back(p);
}

void World::addEnemy(Enemy* e) {
	enemies.push_back(e);
	drawables.push_back(e);
}

void World::removeEnemy(Enemy* e) {
	enemies.remove(e);
	drawables.remove(e);
}

void World::addDrawable(Drawable* d) {
	drawables.push_back(d);
}

void World::removeDrawable(Drawable* d) {
	drawables.remove(d);
}

void World::addExplodable(Explodable* e) {
	dying.push_back(e);

	std::list<Chunk>::const_iterator iter = e->getChunks().begin();

	while (iter != e->getChunks().end()) {
		drawables.push_back( const_cast<Chunk *>(&(*iter)) );
		++iter;
	}
/*
	std::list<Drawable *>::const_iterator iter2 = drawables.begin();
	while (iter2 != drawables.end()) {
		if (dynamic_cast<Chunk *>(*iter2)) {
			std::cout << dynamic_cast<Chunk *>(*iter2)->getWidth() << std::endl;
		}
		++iter2;
	}
	*/
}

void World::removeExplodable(Explodable* e) {
	dying.remove(e);
}
