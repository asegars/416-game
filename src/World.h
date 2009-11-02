/*
 * World.h
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <string>
#include <vector>

#include "Sprite.h"
#include "Drawable.h"
#include "terrain/Terrain.h"
#include "terrain/WorldMap.h"

#ifndef WORLD_H_
#define WORLD_H_

class World : public Drawable {
public:
	World(std::string filename);
	virtual ~World();

	void add(Terrain* t, int cellX, int cellY);
  float getX() const { return 0; }
  float getY() const { return 0; }
  int getXCells() { return worldMap->getCellWidth(); }
  int getYCells() { return worldMap->getCellHeight(); }
	int getWidth() const { return background->getWidth(); }
	int getHeight() const { return background->getHeight(); }
	Sprite* getSprite() const { return background; }
	virtual void updatePosition(Uint32) {}

	void setMap(WorldMap* map);
	WorldMap* getMap() const { return worldMap; }
	Terrain** getTerrain() { return worldMap->getMap(); }
private:
	Sprite* background;
	WorldMap* worldMap;
};

#endif /* WORLD_H_ */
