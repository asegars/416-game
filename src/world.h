#include "frame.h"
#include "viewport.h"

class World {
public:
  World(Frame *f) 
    : frame(f), worldX(0.0), worldY(0.0), view(Viewport::getViewport()) {}
  ~World() { delete frame; }

  void update();
  void draw() { frame->draw(worldX, worldY, 0, 0); }

  float getX() const { return worldX; }
  float getY() const { return worldY; }

private:
  Frame * frame;
  float worldX;
  float worldY;
  Viewport * view;
};
