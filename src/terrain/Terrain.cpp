/*
 * Terrain.cpp
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */

#include "Terrain.h"

int Terrain::width = 80;
int Terrain::height = 80;

Terrain::Terrain(Sprite* terrainSprite) : sprite(terrainSprite) {
	width = sprite->getWidth();
	height = sprite->getHeight();
}

Terrain::~Terrain() {
	if (sprite != NULL) { delete sprite; }
}
