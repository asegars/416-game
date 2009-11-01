/*
 * Terrain.cpp
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */

#include "Terrain.h"

int Terrain::width = 80;
int Terrain::height = 80;

Terrain::Terrain(Sprite* terrainSprite, int x, int y) : sprite(terrainSprite), xLoc(x), yLoc(y) {

}

Terrain::~Terrain() {

}
