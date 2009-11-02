/*
 * Character.cpp
 *
 *  Created on: Oct 25, 2009
 *      Author: luke
 */

#include <iostream>
#include "Character.h"
#include "Manager.h"

Character::Character() {
}

Character::~Character() {
}

bool Character::checkLocationForCollision(float xLoc, float yLoc) {
	int cellIndex = world->getMap()->locationToCell(xLoc, yLoc);
	if (world->getMap()->getCell(cellIndex) == NULL) {
		return false;
	}
	std::cout << "Collision..." << std::endl;
	return true;
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
