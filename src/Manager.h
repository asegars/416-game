/*
 * Manager.h
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include "Camera.h"
#include "World.h"
#include "Player.h"
#include "FontLibrary.h"

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
	Player* getPlayer() const { return player; }
	Camera* getCamera() const { return camera; }
	FontLibrary* getFontLibrary() const { return fontLibrary; }

private:
	Manager();
	void handle_keydown(const SDLKey& key);
	void handle_keyup(const SDLKey& key);
	void move_enemy();

	SDL_Surface* screen;
	Camera* camera;
	World* world;
	Player* player;
	Player* enemy;
	FontLibrary* fontLibrary;

	Uint32 cur_ticks;
	Uint32 prev_ticks;
	Uint32 ticks;

	bool done;

	static Manager* instance;

	int xVel;	// passed as a parameter to move()
	int yVel;	// passed as a parameter to move()
};

#endif /* MANAGER_H_ */
