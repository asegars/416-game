#include <vector>
#include <iostream>
using std::vector;

#include "sprite.h"

void Sprite::draw() { 
  Uint32 x = static_cast<Uint32>(xCoordinate);
  Uint32 y = static_cast<Uint32>(yCoordinate);
  frame->draw(x, y); 
}

void Sprite::update(Uint32 ticks) { 
  float incr = ySpeed * static_cast<float>(ticks) * 0.001;
  yCoordinate += incr;
  float height = static_cast<float>(frame->getHeight());
  if ( yCoordinate <= 0) {
    ySpeed = abs(ySpeed);
  }
  if ( yCoordinate >= WORLD_HEIGHT - height) {
    ySpeed = -abs(ySpeed);
  }

  incr = xSpeed * static_cast<float>(ticks) * 0.001;
  xCoordinate += incr;
  float width = static_cast<float>(frame->getWidth());
  if ( xCoordinate <= 0) {
    xSpeed = abs(xSpeed);
  }
  if ( xCoordinate >= WORLD_WIDTH - width) {
    xSpeed = -abs(xSpeed);
  }
}
