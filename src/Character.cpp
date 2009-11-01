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

bool Character::collidesWithWorld(float xIncr, float yIncr) {
	if (world == NULL) {
		world = Manager::getInstance()->getWorld();
	}

	float newX = x + xIncr;
	float newY = y + yIncr;

	Terrain ** terrain = world->getTerrain();

	int xCells = world->getXCells();
	int yCells = world->getYCells();
	int terrainWidth, terrainHeight, terrainX, terrainY;

	int index = 0;
	for (int yIndex = 0; yIndex < yCells; ++yIndex) {
		for (int xIndex = 0; xIndex < xCells; ++xIndex) {
			index = yIndex * xCells + xIndex;
			Terrain* current = terrain[index];

			if (terrain[index] == NULL) {
				continue;
			}

			terrainWidth = current->getWidth();
			terrainHeight = current->getHeight();
			terrainX = xIndex * terrainWidth;
			terrainY = yIndex * terrainHeight;

			if (terrainX + terrainWidth - 2 < newX) {
				continue;
			}
			if (terrainX > newX + getWidth() - 2) {
				continue;
			}
			if (terrainY + terrainHeight - 2 < newY) {
				continue;
			}
			if (terrainY > newY + getHeight() - 2) {
				continue;
			}
			return true;
		}
	}
	return false;
}
