#include "sprite.h"
#include "viewport.h"

class Fireball : public Sprite {
public:
  Fireball(float x, float y, float xs, float ys, Frame *f)
  : Sprite(x, y, xs, ys, f), view(Viewport::getViewport()) {
    view->setX(0.0);
    view->setY(0.0);
  }

  void update(Uint32 ticks) {
    Sprite::update(ticks);
    fireballX = getX();
    fireballY = getY();
    fireballX -= view->getX();
    fireballY -= view->getY();
  }

  void draw() { 
    Uint32 x = static_cast<Uint32>(fireballX);
    Uint32 y = static_cast<Uint32>(fireballY);
    frame->draw(x, y);
    //cout << fireballX << " " << fireballY << endl;
  }

private:
  Viewport *view;
  float fireballX;
  float fireballY;
};
