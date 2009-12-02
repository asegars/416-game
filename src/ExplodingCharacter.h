/*
 * ExplodingCharacter.h
 *
 *  Created on: Nov 16, 2009
 *  
 */

#ifndef EXPLODINGCHARACTER_H_
#define EXPLODINGCHARACTER_H_

#include "Character.h"
#include "World.h"

const int MAX_DISTANCE = 200;

class ExplodingCharacter : public Character {
public:
	ExplodingCharacter(float nx, float ny, float sX, float sY, Sprite *s, 
      World *w) {
    setX(nx);
    setY(ny);
    setXSpeed(sX);
    setYSpeed(sY);
    distance = 0;
    tooFar = false;
    world = w;
    sprites.push_back(s);
  }
	virtual ~ExplodingCharacter() {}

	virtual void updatePosition(Uint32 ticks);
  bool goneTooFar() const { return tooFar; }
  void reset() {
    tooFar = false;
    distance = 0;
  }
  virtual Sprite* getSprite() const { return sprites.at(0); }
  // virtual float getX() { return x; }
  // virtual float getY() { return y; }

private:
  float distance;
  bool tooFar;
  World* world;
};

#endif /* EXPLODINGCHARACTER_H_ */
