/*
 * Chunk.cpp
 *
 *  Created on: Nov 16, 2009
 *  
 */

#include <iostream>
#include "Chunk.h"

Chunk::Chunk(Sprite* piece, float x, float y, float dx, float dy) {
	setX(x);
	setY(y);
	setXSpeed(dx);
	setYSpeed(dy);


	std::cout << x  << ", " << y << ", " << dx << ", " << dy << std::endl;
	sprite = piece;
}

Chunk::~Chunk() {
	if (sprite != NULL) delete sprite;
}
