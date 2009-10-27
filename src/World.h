/*
 * World.h
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <string>

#include "Sprite.h"
#include "Drawable.h"

#ifndef WORLD_H_
#define WORLD_H_

class World : public Drawable {
public:
	World(std::string filename);
	virtual ~World();

  float getX() const { return 0; }
  float getY() const { return 0; }
	int getWidth() const { return background->getWidth(); }
	int getHeight() const { return background->getHeight(); }
	Sprite* getSprite() const { return background; }
	virtual void updatePosition(Uint32 ticks) {}
private:
	Sprite* background;
};

#endif /* WORLD_H_ */
