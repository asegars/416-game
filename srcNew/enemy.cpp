#include "enemy.h"

void Enemy::update(Uint32 ticks) {
  float incr = xSpeed * static_cast<float>(ticks) * 0.001;
  xCoordinate += incr;
  float width = static_cast<float>(frames->at(curFrame).getWidth());
  if ( xCoordinate <= 0) {
    xSpeed = abs(xSpeed);
  }
  if ( xCoordinate >= WORLD_WIDTH - width) {
    xSpeed = -abs(xSpeed);
  }

  yCoordinate = WORLD_HEIGHT - getHeight();
  advanceFrame(ticks);
}

void Enemy::advanceFrame(Uint32 ticks) {
  interval += ticks;
  if (fabs(interval * xSpeed) > 15000 && xSpeed > 0) {
    curFrame = (++curFrame);
    if(curFrame > 2)
      curFrame = 0;
    interval = 0;
  }
  else if (fabs(interval * xSpeed) > 15000 && xSpeed < 0) {
    curFrame = (++curFrame) % (frames->size());
    if(curFrame < 3)
      curFrame = 3;
    interval = 0;
  }
}
