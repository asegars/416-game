/*
 * SolidTerrain.cpp
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */

#include "SolidTerrain.h"

SolidTerrain::SolidTerrain(int x, int y) : Terrain(new Sprite("images/solid-terrain.png"), x, y) {
}

SolidTerrain::~SolidTerrain() {

}
