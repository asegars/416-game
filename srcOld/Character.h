/*
 * Character.h
 *
 *  Created on: Oct 25, 2009
 *      Author: luke
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include "Drawable.h"
#include "Sprite.h"
#include "World.h"

// TODO: These constants should be stored somewhere else.
enum CollisionType {NO_COLLIDE, COLLIDE_TOP, COLLIDE_BOTTOM, COLLIDE_LEFT, COLLIDE_RIGHT};

class Character : public Drawable {
public:
	Character();
	virtual ~Character();

  bool collidesWithWorld(float xIncr, float yIncr);
  float getX() const { return x; }
  float getY() const { return y; }
  void setX(float nx) { x = nx; }
  void setY(float ny) { y = ny; }
  float getXSpeed() const { return xSpeed; }
  float getYSpeed() const { return ySpeed; }
  int getWidth() const { return sprites.at(curSprite)->getWidth(); }
  int getHeight() const { return sprites.at(curSprite)->getHeight(); }

protected:
  float x;
  float y;

  float xSpeed;
  float ySpeed;

  std::vector<Sprite*> sprites;
  unsigned int curSprite;
private:
  bool checkLocationForCollision(float xLoc, float yLoc);
  World* world;
};

#endif /* CHARACTER_H_ */
