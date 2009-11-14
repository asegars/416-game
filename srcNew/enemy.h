#include "sprite.h"
#include "viewport.h"

const int ENEMY_SPEED = 120;

class Enemy : public Drawable {
public:
  Enemy(float x, float y, float xs, float ys)
  : Drawable(x, y, xs, ys), view(Viewport::getViewport()) { }

  void update(Uint32);
  void advanceFrame(Uint32);

  void setFrames(vector<Frame> * f) { 
    frames = f; 
    curFrame = 0;
    interval = 0;
  }
  void draw() { 
    Uint32 x = static_cast<Uint32>((xCoordinate - view->getX()));
    Uint32 y = static_cast<Uint32>((yCoordinate - view->getY()));
    frames->at(curFrame).draw(x, y);
  }

  float getHeight() const { return frames->at(curFrame).getHeight(); }
  float getWidth() const { return frames->at(curFrame).getWidth(); }

private:
  Viewport *view;
  vector<Frame> *frames;
  unsigned int curFrame;
  int interval;
  float enemyX;
  float enemyY;
};
