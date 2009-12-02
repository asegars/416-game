/*
 * Explodable.h
 *
 *  Created on: Nov 16, 2009
 *  
 */

#ifndef EXPLODABLE_H_
#define EXPLODABLE_H_

#include <list>
#include "ExplodingCharacter.h"

const int CHUNKS = 15;

class Explodable : public Character {
public:
  Explodable() {}
	Explodable(int, int, Sprite*, World*);
	virtual ~Explodable();

  void makeChunks(unsigned int);
  // unsigned int chunkCount() const { return chunks.size(); }
	virtual void updatePosition(Uint32);
  virtual Sprite* getSprite() const { return sprites.at(0); }

private:
  // std::vector<ExplodingCharacter> chunks;
  World* world;
};

#endif /* EXPLODABLE_H_ */
