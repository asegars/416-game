/*
 * World.h
 *
 *  Created on: Oct 6, 2009
 */

#ifndef WORLD_H_
#define WORLD_H_

#include <list>

#include "Sprite.h"
#include "Drawable.h"
#include "Explodable.h"
#include "terrain/Terrain.h"
#include "terrain/WorldMap.h"

class Player;
class Enemy;
class Explodable;

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

	// Map functions
	void setMap(WorldMap* map);
	WorldMap* getMap() { return worldMap; }
	std::list<Terrain*> getTerrain() { return worldMap->getMap(); }
	Terrain** getTerrainArray() { return worldMap->getMapArray(); }

	// Drawables and individual units
	void assignPlayer(Player* p);
	void addEnemy(Enemy* e);
	void removeEnemy(Enemy* e);
	void addDrawable(Drawable* d);
	void removeDrawable(Drawable* d);
	void addExplodable(Explodable* e);
	void removeExplodable(Explodable* e);
	const std::list<Enemy *>& getEnemies() const { return enemies; }
	const std::list<Explodable *>& getExplodables() const { return dying; }

	const std::list<Drawable *>& getDrawables() { return drawables; }
private:
	Sprite* background;
	WorldMap* worldMap;

	Player* player;
	std::list<Enemy *> enemies;
	std::list<Drawable *> drawables;
	std::list<Explodable *> dying;
};

#endif /* WORLD_H_ */
