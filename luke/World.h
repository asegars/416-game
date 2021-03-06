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

const int NUM_BACKGROUNDS = 3;

class World : public Drawable {
public:
	World(std::string filename);
	virtual ~World();

	int getWidth() const { return background->getWidth(); }
	int getHeight() const { return background->getHeight(); }
	Sprite* getSprite() const { return background; }
	virtual void updatePosition(Uint32 ticks) {}
private:
	Sprite* background;
};

#endif /* WORLD_H_ */
