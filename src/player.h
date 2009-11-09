#include "sprite.h"
#include "viewport.h"

const int MAX_SPEED = 200;
const int MAX_JUMP = 400;
const int DECEL = 0.95;

class Player : public Drawable {
public:
  Player() : Drawable(50, 48, 0, 0), view(Viewport::getViewport()), 
    falling(false), isHit(false) {}
  Player(float x, float y, float xs, float ys)
  : Drawable(x, y, xs, ys), view(Viewport::getViewport()), falling (true),
    isHit(false) {}

  void update(Uint32);
  void advanceFrame(Uint32);
  void draw() { 
    Uint32 x = static_cast<Uint32>((xCoordinate - view->getX()));
    Uint32 y = static_cast<Uint32>((yCoordinate - view->getY()));
    frames->at(curFrame).draw(x, y); 
  }

  void setFrames(vector<Frame> * f) { 
    frames = f; 
    curFrame = 0;
    interval = 0;
  }

  void incrSpeedX();
	void decrSpeedX();
	void decelX();
	void decelY();
  void jump();

  float getHeight() const { return frames->at(curFrame).getHeight(); }
  float getWidth() const { return frames->at(curFrame).getWidth(); }
  float getXSpeed() const { return xSpeed; }
  float getYSpeed() const { return ySpeed; }
  void setHit(bool hit) { isHit = hit; }
  bool wasHit() const { return isHit; }
  bool isFalling() const { return falling; }

private:
  Viewport *view;
  vector<Frame> *frames;
  unsigned int curFrame;
  int interval;
  float playerX;
  float playerY;
  bool falling;
  bool isHit;
};
