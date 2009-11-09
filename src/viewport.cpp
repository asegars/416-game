#include "viewport.h"

Viewport* Viewport::getViewport() {
	if (!instance) {
		instance = new Viewport();
	}
	return instance;
}

void Viewport::trackObject(Drawable *obj) { 
  object = obj;
}

void Viewport::update() {
  float x = object->getX();
  float y = object->getY();
  viewX = (x + 20) - VIEW_WIDTH/2;
  viewY = (y + 24) - VIEW_HEIGHT/2;
  if (viewX < 0) viewX = 0;
  if (viewY < 0) viewY = 0;
  if (viewX > (WORLD_WIDTH - VIEW_WIDTH)) {
    viewX = WORLD_WIDTH-VIEW_WIDTH;
  }
  if (viewY > (WORLD_HEIGHT - VIEW_HEIGHT)) {
    viewY = WORLD_HEIGHT-VIEW_HEIGHT;
  }
}
