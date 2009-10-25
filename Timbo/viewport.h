#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "drawable.h"

class Viewport {
public:
  static Viewport* getViewport() {
    if (!instance) {
      instance = new Viewport;
    }
    return instance;
  }

  float getX() const { return myX; }
  float getY() const { return myY; }

  void setX(float x) { myX = x; }
  void setY(float y) { myY = y; }

private:
  Viewport() {}
  static Viewport  *instance;
  float myX;
  float myY;
};

#endif
