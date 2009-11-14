#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "sprite.h"

const int VIEW_WIDTH = 800;
const int VIEW_HEIGHT = 600;

class Viewport {
public:
  static Viewport* getViewport();
  void update();

  float getX() const { return viewX; }
  float getY() const { return viewY; }

  void setX(float x) { viewX = x; }
  void setY(float y) { viewY = y; }

  void trackObject(Drawable *);

private:
  Viewport() {}
  static Viewport *instance;
  float viewX;
  float viewY;
  Drawable *object;
};
#endif
