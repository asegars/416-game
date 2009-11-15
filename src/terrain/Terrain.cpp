/*
 * Terrain.cpp
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */

#include "Terrain.h"

int Terrain::width = 30;
int Terrain::height = 30;

Terrain::Terrain(Sprite* terrainSprite) : sprite(terrainSprite) {
	width = sprite->getWidth();
	height = sprite->getHeight();
}

Terrain::~Terrain() {
//	if (sprite != NULL) { delete sprite; }
}
