/*
 * ExplodingCharacter.cpp
 *
 *  Created on: Nov 16, 2009
 *  
 */

#include <iostream>
#include "Chunk.h"
#include "ExplodingCharacter.h"

ExplodingCharacter::ExplodingCharacter(Character* w, unsigned int chunks) {
	whole = w;
	numChunks = chunks;

	x = w->getX();
	y = w->getY();

	createChunks();
	std::cout << "Full size: " << w->getWidth() << ", " << w->getHeight() << std::endl;
	std::cout << "Exploding character created" << std::endl;
}

void ExplodingCharacter::createChunks() {
	int explosionSpeed = 220;

	float startX, startY, dx, dy;
	float spriteX, spriteY;
	Sprite* sprite = whole->getSprite();

	for (unsigned int i = 0; i < numChunks; ++i) {
		startX = whole->getX() + (.5 * whole->getWidth());
		startY = whole->getY() + (.5 * whole->getHeight());

		spriteX = (rand() % (sprite->getWidth() - 8));
		spriteY = (rand() % (sprite->getHeight() - 8));

		dx = (rand() % explosionSpeed + 40) * ( (rand() % 2) ? -1 : 1 );
		dy = (rand() % explosionSpeed + 40) * ( (rand() % 2) ? -1 : 1 );

		Chunk chunk(new Sprite(spriteX, spriteY, 4, 4, sprite->getSurface()),
				startX, startY,	dx, dy);
		chunks.push_back(chunk);
	}
}

ExplodingCharacter::~ExplodingCharacter() {

}

const std::list<Chunk>& ExplodingCharacter::getChunks() const {
	return chunks;
}


void ExplodingCharacter::updatePosition(Uint32 ticks) {
	std::list<Chunk>::iterator iter = chunks.begin();
	// Let each chunk update itself
	while (iter != chunks.end()) {
		iter->updatePosition(ticks);

		// Expand the bounding box as necessary.
		if (iter->getX() < x) x = iter->getX();
		if (iter->getY() < y) y = iter->getY();

		++iter;
	}
}

float ExplodingCharacter::getX() const {
	return x;
}

float ExplodingCharacter::getY() const {
	return y;
}
