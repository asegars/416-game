/*
 * Manager.h
 *
 *  Created on: Oct 6, 2009
 */
#include <iostream>
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "Enemy.h"
#include "FontLibrary.h"
#include "Background.h"
#include "Target.h"

#ifndef MANAGER_H_
#define MANAGER_H_

class Manager {
public:
	static Manager* getInstance() {
		if (instance == NULL) {
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
	Target* getTarget() { return target; }

	void reportVictory() { if (!defeat) victory = true; }
	void reportDefeat() { if (!victory) defeat = true; }
  void incrPlayerScore(int score) { playerScore += score; }
	void setMap(WorldMap* map) { world->setMap(map); }

private:
	Manager();
  void loadHero();
  void loadEnemies();
  int getScore();
  void checkDeathConditions();
  void checkVictoryConditions();

	SDL_Surface* screen;
	Camera* camera;
	World* world;
	Background* background;
	Player* player;
	Target* target;
	Enemy* enemy;
	vector<Enemy*> enemies;
	FontLibrary* fontLibrary;

	Uint32 cur_ticks;
	Uint32 prev_ticks;
	Uint32 ticks;

	bool done;
	int playerScore;
  int health;
	bool victory, defeat;
	int overlayAlpha;
	static Manager* instance;
	vector<Sprite*> heroSprites;
	vector<Sprite*> enemySprites;

	// Special mode sprites
	Sprite* victorySprite;
	Sprite* defeatSprite;
};

#endif /* MANAGER_H_ */
