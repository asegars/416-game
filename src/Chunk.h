/*
 * Chunk.h
 *
 *  Created on: Nov 16, 2009
 *  
 */

#ifndef CHUNK_H_
#define CHUNK_H_

#include <iostream>
#include "Character.h"
#include "Sprite.h"

class Chunk : public Character {
public:
	Chunk(Sprite* piece, float x, float y, float dx, float dy);
	virtual ~Chunk();

	virtual int getWidth() const { return sprite->getWidth(); }
	virtual int getHeight() const { return sprite->getHeight(); }
	virtual Sprite* getSprite() const { std::cout << sprite->getWidth() << std::endl; return sprite; }

private:
	Sprite* sprite;
};

#endif /* CHUNK_H_ */
