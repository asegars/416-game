/*
 * Explodable.h
 *
 *  Created on: Nov 16, 2009
 *  
 */

#ifndef EXPLODABLE_H_
#define EXPLODABLE_H_

#include <list>
#include "Chunk.h"

class Chunk;

class Explodable {
public:
	Explodable();
	virtual ~Explodable();

	virtual const std::list<Chunk>& getChunks() const = 0;
	virtual float getX() const = 0;
	virtual float getY() const = 0;
	virtual void updatePosition(Uint32 ticks) = 0;
};

#endif /* EXPLODABLE_H_ */
