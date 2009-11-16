/*
 * Character.cpp
 *
 *  Created on: Oct 25, 2009
 */

#include <iostream>
#include "Character.h"
#include "Manager.h"
#include "ExplodingCharacter.h"

Character::Character() {
}

Character::~Character() {
}

bool Character::checkLocationForCollision(float xLoc, float yLoc) {
	WorldMap* map = world->getMap();

	if (map != NULL) {
		int cellIndex = map->locationToCell(xLoc, yLoc);

		if (world->getTerrainArray()[cellIndex] == 0) {
			return false;
		}
		return true;
	}
	return false;
}

bool Character::collidesWithWorld(float x, float y, float w, float h, float dx, float dy) {
	// If moving right, add the width of the character
//	if (dx > 0) { x += w; }
	// If falling down, add the height of the character
//	if (dy > 0) { y += w; }
	WorldMap* map = world->getMap();

	int cell = map->locationToCell(x + dx, y + dy);
	int cellX = cell % map->getCellWidth();
	int cellY = cell / map->getCellWidth();

	int tX = cellX * map->getCellDim();
	int tY = cellY * map->getCellDim();
	int tW = map->getCellDim();
	int tH = map->getCellDim();

	if ( (x + w >= tX) &&
			 (x <= tX + tW) &&
			 (y + h >= tY) &&
			 (y <= tY + tH) ) {
		return true;
	}
	else {
		return false;
	}
}

bool Character::collidesWithWorld(float xIncr, float yIncr) {
	world = Manager::getInstance()->getWorld();

	float newX = x + xIncr;
	float newY = y + yIncr;
	// If moving right, add the width of the character
	if (xIncr > 0) { newX += getWidth(); }
	// If falling down, add the height of the character
	if (yIncr > 0) { newY += getHeight(); }

	return checkLocationForCollision(newX, newY);
}

void Character::updatePosition(Uint32 ticks) {
	float yIncr = ySpeed * static_cast<float> (ticks) * 0.001;
	float xIncr = xSpeed * static_cast<float> (ticks) * 0.001;

	x += xIncr;
	y += yIncr;
}

// TODO: Exploding is the most troublesome thing ever....
void Character::explode() {
	if (world == NULL) world = Manager::getInstance()->getWorld();

//	ExplodingCharacter* exploder = new ExplodingCharacter(this);
//	world->addExplodable(exploder);

	// TODO: Get rid of the dynamic_cast
	Enemy* e_ptr = dynamic_cast<Enemy *>(this);
	if (e_ptr != NULL) {
		world->removeEnemy(e_ptr);
	}
}
