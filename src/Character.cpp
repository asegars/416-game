/*
 * Character.cpp
 *
 *  Created on: Oct 25, 2009
 */

#include <iostream>
#include "Character.h"
#include "Manager.h"

Character::Character() {
}

Character::~Character() {
}

bool Character::checkLocationForCollision(float xLoc, float yLoc) {
	if (world == NULL) {
		world = Manager::getInstance()->getWorld();
	}
	WorldMap* map = world->getMap();

	if (map != NULL) {
		int cellIndex = map->locationToCell(xLoc, yLoc);

		if (world->getTerrain()[cellIndex] == NULL) {
			return false;
		}
		return true;
	}
	return false;
}

bool Character::collidesWithWorld(float xIncr, float yIncr) {
	if (world == NULL) {
		world = Manager::getInstance()->getWorld();
	}

	float newX = x + xIncr;
	float newY = y + yIncr;
	// If moving right, add the width of the character
	if (xIncr > 0) { newX += getWidth(); }
	// If falling down, add the height of the character
	if (yIncr > 0) { newY += getHeight(); }

	return checkLocationForCollision(newX, newY);
}
