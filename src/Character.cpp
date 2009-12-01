/*
 * Character.cpp
 *
 *  Created on: Oct 25, 2009
 */

#include <iostream>
#include "Character.h"
#include "Manager.h"
#include "ExplodingCharacter.h"

Character::Character() {}

Character::~Character() {}

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

bool Character::collidesWith(Character* c) {
	if (x > c->getX() &&
		x < c->getX() + c->getWidth() &&
		y > c->getY() &&
		y < c->getY() + c->getHeight()) {
			return true;
	}

	if (x + getWidth()  > c->getX() &&
		x + getWidth()  < c->getX() + c->getWidth() &&
		y + getHeight() > c->getY() &&
		y + getHeight() < c->getY() + c->getHeight()) {
			return true;
	}
	return false;
}

CollisionType Character::checkRectForCollision(float tlx, float tly, float brx, float bry) {
	WorldMap* map = world->getMap();
	Terrain** terrain = world->getTerrainArray();
	int numChecks = 8;
	int cellIndex[numChecks];

	if (map != NULL) {
		// Check the four corners
		cellIndex[0] = map->locationToCell(tlx, tly);
		cellIndex[1] = map->locationToCell(tlx, bry);
		cellIndex[2] = map->locationToCell(brx, tly);
		cellIndex[3] = map->locationToCell(brx, bry);

		// Check the midpoints between each corner.
		// Middle left
		cellIndex[4] = map->locationToCell(tlx, tly + abs(bry - tly) / 2);
		// Middle top
		cellIndex[5] = map->locationToCell(tlx + abs(brx - tlx) / 2, tly);
		// Middle right
		cellIndex[6] = map->locationToCell(brx, tly + abs(bry - tly) / 2);
		// Middle bottom
		cellIndex[7] = map->locationToCell(tlx + abs(brx - tlx) / 2, bry);

		for (int i = 0; i < numChecks; ++i) {
			if (terrain[cellIndex[i]] != NULL) return true;
		}
		return false;
	}
	else {
		throw std::string("No map defined for the game world!");
		return false;
	}
}

CollisionType Character::collidesWithWorld(float xIncr, float yIncr) {
	world = Manager::getInstance()->getWorld();

	float tlx, tly, brx, bry;

	tlx = x + xIncr;
	tly = y + yIncr;
	brx = tlx + getWidth();
	bry = tly + getHeight();

	return checkRectForCollision(tlx, tly, brx, bry);
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

  world->addExplodable(new Explodable(sprites.at(curSprite)));

	// TODO: Get rid of the dynamic_cast
	Enemy* e_ptr = dynamic_cast<Enemy *>(this);
	if (e_ptr != NULL) {
		world->removeEnemy(e_ptr);
    world->removeDrawable(e_ptr);
	}
}
