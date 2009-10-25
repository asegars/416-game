#include "sprite.h"
#include "viewport.h"

const int MAX_SPEED = 300;
const int DECEL = 0.97;

class Player : public Sprite {
public:
  Player(float x, float y, float xs, float ys, Frame *f)
  : Sprite(x, y, xs, ys, f), view(Viewport::getViewport()) {
    view->setX(0.0);
    view->setY(0.0);
  }

  void update(Uint32);

  void draw() { 
    Uint32 x = static_cast<Uint32>(playerX);
    Uint32 y = static_cast<Uint32>(playerY);
    frame->draw(x, y); 
  }

  void incrSpeedX();
	void decrSpeedX();
	void incrSpeedY();
	void decrSpeedY();
	void decelX();
	void decelY();

  float getXSpeed() const { return xSpeed; }
  float getYSpeed() const { return ySpeed; }

private:
  Viewport *view;
  float playerX;
  float playerY;
};
