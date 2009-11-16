/*
 * ExplodingCharacter.h
 *
 *  Created on: Nov 16, 2009
 *  
 */

#ifndef EXPLODINGCHARACTER_H_
#define EXPLODINGCHARACTER_H_

#include "Chunk.h"
#include "Explodable.h"

class ExplodingCharacter : public Explodable {
public:
	ExplodingCharacter(Character* w, unsigned int chunks = 20);
	virtual ~ExplodingCharacter();

	virtual float getX() const;
	virtual float getY() const;
	virtual void updatePosition(Uint32 ticks);
	virtual const std::list<Chunk>& getChunks() const;

private:
	void createChunks();

	Character* whole;
	unsigned int numChunks;
	std::list<Chunk> chunks;

	float x, y;
};

#endif /* EXPLODINGCHARACTER_H_ */
