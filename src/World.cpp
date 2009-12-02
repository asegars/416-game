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

	waves.push_back(new Sprite("wave/wave-dark.bmp"));
	waves.push_back(new Sprite("wave/wave-light.bmp"));
	waves.push_back(new Sprite("wave/wave-mid.bmp"));

	waveVelocity[0] = 1.0;
	waveVelocity[1] = 1.2;
	waveVelocity[2] = 1.4;
}

World::~World() {
	if (background != NULL) delete background;
	if (worldMap != NULL) delete worldMap;

	for (unsigned int i = 0; i < waves.size(); ++i) {
		delete waves[i];
	}
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
  //drawables.push_back(e);
}

void World::removeExplodable(Explodable* e) {
	dying.remove(e);
  //drawables.remove(e);
}

bool World::playerCollision() {

	float enemyWidth;
	float enemyHeight;
	float playerWidth = player->getWidth();
	float playerHeight = player->getHeight();

  std::list<Enemy*>::iterator iter = enemies.begin();

	for (iter = enemies.begin(); iter != enemies.end(); ++iter) {
		enemyWidth = (*iter)->getWidth();
		enemyHeight = (*iter)->getHeight();
		if ((*iter)->getX() + enemyWidth - 5 < player->getX()) {
			continue;
		}
		if ((*iter)->getX() > player->getX() + playerWidth - 5) {
			continue;
		}
		if ((*iter)->getY() + enemyHeight - 5 < player->getY()) {
			continue;
		}
		if ((*iter)->getY() > player->getY() + playerHeight - 5) {
			continue;
		}
		return true;
	}

	return false;
}
