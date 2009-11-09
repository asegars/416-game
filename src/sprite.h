#ifndef SPRITE__H
#define SPRITE__H

#include <vector>
#include <string>
#include <iostream>
using std::vector;

#include "drawable.h"
#include "frame.h"

class Sprite : public Drawable {
public:
  Sprite(float x, float y, float xs, float ys, Frame* f) : 
    Drawable(x, y, xs, ys), frame(f) { }

  Sprite(const Sprite& s) :
    Drawable(s.xCoordinate, s.yCoordinate, s.xSpeed, s.ySpeed), 
             frame(s.frame) { }
  virtual ~Sprite() {} 

  Frame *getFrame() const { return frame; }
  void deleteFrame() { delete frame; }

  virtual void draw();
  virtual void update(Uint32 ticks);

protected:
  Frame *frame;
};
#endif
