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

CollisionType Character::checkRectForCollision(float tlx, float tly, float brx, float bry) {
	WorldMap* map = world->getMap();
	Terrain** terrain = world->getTerrainArray();
	CollisionType collision = NO_COLLISION;
	int numChecks = 8;
	int cellIndex[numChecks];

//	std::cout << "[" << tlx << ", " << tly << "] - [" << brx << ", " << bry << "]" << std::endl;

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
		/*
		if (terrain[cellIndex[0]] != NULL) {
//			collision = collision | (COLLIDE_LEFT | COLLIDE_TOP);
//			std::cout << collision << std::endl;
//			std::cout << "Colliding in TL" << std::endl;
//			return true;
		}
		if (terrain[cellIndex[1]] != NULL) {
//			collision = collision | (COLLIDE_RIGHT | COLLIDE_TOP);
//			std::cout << "Colliding in TR" << std::endl;
//			return true;
		}
		if (terrain[cellIndex[2]] != NULL) {
//			collision = collision | (COLLIDE_BOTTOM | COLLIDE_LEFT);
//			std::cout << collision << std::endl;
//			std::cout << "Colliding in BL" << std::endl;
//			return true;
		}
		if (terrain[cellIndex[3]] != NULL) {
//			collision = collision | (COLLIDE_RIGHT | COLLIDE_BOTTOM);
//			std::cout << "Colliding in BR" << std::endl;
//			return true;
		}
		if (terrain[cellIndex[4]] != NULL) {
			collision = collision | COLLIDE_LEFT;
//			std::cout << collision << std::endl;
//			std::cout << "Colliding in ML" << std::endl;
//			return true;
		}
		if (terrain[cellIndex[5]] != NULL) {
			collision = collision | COLLIDE_TOP;
//			std::cout << "Colliding in MT" << std::endl;
//			return true;
		}
		if (terrain[cellIndex[6]] != NULL) {
			collision = collision | COLLIDE_RIGHT;
//			std::cout << "Colliding in MR" << std::endl;
//			return true;
		}
		if (terrain[cellIndex[7]] != NULL) {
			collision = collision | COLLIDE_BOTTOM;
//			std::cout << "Colliding in MB" << std::endl;
//			return true;
		}

		return collision;
		*/
//		return (collision != NO_COLLISION) ? true : false;
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

	// If moving right, add the width of the character
//	if (xIncr > 0) { newX += getWidth(); }
	// If falling down, add the height of the character
//	if (yIncr > 0) { newY += getHeight(); }

	return checkRectForCollision(tlx, tly, brx, bry);
//	return checkLocationForCollision(newX, newY);
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
