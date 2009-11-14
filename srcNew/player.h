#include "sprite.h"
#include "viewport.h"

const int MAX_SPEED = 200;
const int MAX_JUMP = 500;
const int DECEL = 0.95;

class Player : public Drawable {
public:
  Player() : Drawable(50, 48, 0, 0), view(Viewport::getViewport()), 
    fireDir(1), falling(false), isHit(false), justFired(false) {}
  Player(float x, float y, float xs, float ys)
  : Drawable(x, y, xs, ys), view(Viewport::getViewport()), fireDir(1),
    falling (true), isHit(false), justFired(false)  {}

  void update(Uint32);
  void advanceFrame(Uint32);
  void advanceFireFrame(Uint32);
  void draw() { 
    Uint32 x = static_cast<Uint32>((xCoordinate - view->getX()));
    Uint32 y = static_cast<Uint32>((yCoordinate - view->getY()));
    frames->at(curFrame).draw(x, y); 
  }

  void setFrames(vector<Frame> * f) { 
    frames = f; 
    curFrame = 0;
    interval = 0;
    fireInterval = 0;
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
  void setXSpeed(const float f) { xSpeed = f; }
  void setHit(bool hit) { isHit = hit; }
  void setFire(bool fire, float d) {
    justFired = fire; 
    fireDir = d;
  }
  bool wasHit() const { return isHit; }
  bool recentlyFired() const { return justFired; }
  bool isFalling() const { return falling; }

private:
  Viewport *view;
  vector<Frame> *frames;
  unsigned int curFrame;
  int interval;
  int fireInterval;
  float playerX;
  float playerY;
  float fireDir;
  bool falling;
  bool isHit;
  bool justFired;

};
