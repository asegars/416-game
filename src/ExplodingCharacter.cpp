/*
 * ExplodingCharacter.cpp
 *
 *  Created on: Nov 16, 2009
 *  
 */

#include <iostream>
#include <cmath>
#include "ExplodingCharacter.h"

void ExplodingCharacter::updatePosition(Uint32 ticks) {
  float yincr = ySpeed * static_cast<float>(ticks) * 0.001;
  y -= yincr;
  float xincr = xSpeed * static_cast<float>(ticks) * 0.001;
  x -= xincr;
  distance += (fabs(xincr) + fabs(yincr));
  if (distance > MAX_DISTANCE)
    world->removeDrawable(this);
}
