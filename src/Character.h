/*
 * Character.h
 *
 *  Created on: Oct 25, 2009
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include <vector>
#include "Drawable.h"
#include "Sprite.h"
//#include "World.h"

class World;

// TODO: These constants should be stored somewhere else.
enum CollisionType {NO_COLLIDE, COLLIDE_TOP, COLLIDE_BOTTOM, COLLIDE_LEFT, COLLIDE_RIGHT};


class Character : public Drawable {
public:
	Character();
	virtual ~Character();

  bool collidesWithWorld(float xIncr, float yIncr);
  bool collidesWithWorld(float x, float y, float w, float h, float dx, float dy);
  virtual float getX() const { return x; }
  virtual float getY() const { return y; }
  void setX(float nx) { x = nx; }
  void setY(float ny) { y = ny; }
  float getXSpeed() const { return xSpeed; }
  float getYSpeed() const { return ySpeed; }
  void setXSpeed(float dx) { xSpeed = dx; }
  void setYSpeed(float dy) { ySpeed = dy; }
  virtual int getWidth() const { return sprites.at(curSprite)->getWidth(); }
  virtual int getHeight() const { return sprites.at(curSprite)->getHeight(); }

  void explode();
  virtual void updatePosition(Uint32 ticks);

protected:
  float x;
  float y;

  float xSpeed;
  float ySpeed;

  std::vector<Sprite*> sprites;
  unsigned int curSprite;

protected:
  World* world;

private:
  bool checkLocationForCollision(float xLoc, float yLoc);
};

#endif /* CHARACTER_H_ */
