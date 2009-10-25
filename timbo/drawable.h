#ifndef DRAWABLE__H
#define DRAWABLE__H
#include <SDL.h>
#include <iostream>

const int WORLD_WIDTH = 1280;
const int WORLD_HEIGHT = 960;

const int VIEW_WIDTH = 640;
const int VIEW_HEIGHT = 480;
const int CUSHIONX = VIEW_WIDTH/2 - 35;
const int CUSHIONY = VIEW_HEIGHT/2 - 45;

// Drawable is an Abstract Base Class (ABC) that
// specifies the methods that derived classes may
// and must have.
class Drawable {
public:
  Drawable(float x, float y, float xs, float ys) : 
    xCoordinate(x), yCoordinate(y), xSpeed(xs), ySpeed(ys),
    initSpeedX(xSpeed), initSpeedY(ySpeed) { }

  Drawable(const Drawable& s) :
    xCoordinate(s.xCoordinate), yCoordinate(s.yCoordinate),
    xSpeed(s.xSpeed), ySpeed(s.ySpeed) { }

  virtual ~Drawable() {}

  virtual void draw() = 0;
  virtual void update(Uint32 ticks) = 0;

  float getX() const { return xCoordinate; }
  float getY() const { return yCoordinate; }
  void setX(float x) { xCoordinate = x; }
  void setY(float y) { yCoordinate = y; }

protected:
  float xCoordinate;
  float yCoordinate;
  float xSpeed;
  float ySpeed;
  float initSpeedX;
  float initSpeedY;
};

#endif
