#include "frame.h"
#include "viewport.h"

class World {
public:
  World(Frame *f, Frame *f2) 
    : frame(f), frame2(f2), worldX(0.0), worldY(0.0), world2X(0.0), world2Y(0.0),
      view(Viewport::getViewport()) {}
  ~World() { delete frame;  delete frame2; }

  void update();
  void draw();

  float getX() const { return worldX; }
  float getY() const { return worldY; }

private:
  Frame *frame;
  Frame *frame2;
  float worldX;
  float worldY;
  float world2X;
  float world2Y;
  Viewport *view;
};
