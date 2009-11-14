#include <iostream>
#include "world.h"

float min(float x, float y) { return (x < y) ? x : y; }

void World::update() {
  worldX = view->getX();
  worldY = view->getY();

  world2X = view->getX() / 2;
  world2Y = view->getY() / 2;
}

void World::draw() {
  frame->draw(worldX, worldY, 0, 0);
  frame2->draw(world2X, world2Y, 0, 0);
}

