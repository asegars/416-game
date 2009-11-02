/*
 * Manager.h
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <iostream>
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "FontLibrary.h"
#include "Background.h"

#ifndef MANAGER_H_
#define MANAGER_H_

class Manager {
public:
	static Manager* getInstance() {
		if (instance == NULL) {
			std::cout << "Creating new manager" << std::endl;
			instance = new Manager();
		}
		return instance;
	}
	virtual ~Manager();
	void play();

	World* getWorld() const { return world; }
  Background* getBack() const { return background; }
	Player* getPlayer() const { return player; }
  Enemy* getEnemy() const { return enemy; }
	Camera* getCamera() const { return camera; }
	FontLibrary* getFontLibrary() const { return fontLibrary; }

private:
	Manager();
  void loadHero();
  void loadEnemies();
  void loadTerrain();
  bool collision();

	SDL_Surface* screen;
	Camera* camera;
	World* world;
  Background* background;
	Player* player;
  Enemy* enemy;
	vector<Enemy*> enemies;
	FontLibrary* fontLibrary;

	Uint32 cur_ticks;
	Uint32 prev_ticks;
	Uint32 ticks;

	bool done;
	static Manager* instance;
  vector<Sprite*> *heroSprites;
  vector<Sprite*> *enemySprites;

	int xVel;	// passed as a parameter to move()
	int yVel;	// passed as a parameter to move()
};

#endif /* MANAGER_H_ */
