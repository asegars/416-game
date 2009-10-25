#include <iostream>
#include "world.h"

float min(float x, float y) { return (x < y) ? x : y; }

void World::update() {
  worldX = view->getX();
  worldY = view->getY();
  //std::cout <<  "worldX: " << worldX << std::endl;
  //std::cout <<  "worldY: " << worldY << std::endl;
}

