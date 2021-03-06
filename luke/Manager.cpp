/*
 * Manager.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <SDL/SDL.h>
#include <string>
#include <iostream>
#include "Manager.h"

#define WORLD_WIDTH 	800
#define WORLD_HEIGHT 	600

Manager::Manager() {
	screen = SDL_SetVideoMode(WORLD_WIDTH, WORLD_HEIGHT, 16, SDL_HWSURFACE);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::string("Unable to initialize SDL: ");
	}
	if (screen == NULL) {
		throw std::string("Unable to set video mode!");
	}

	world = new World("images/waterfall.bmp");
	camera = new Camera(world, WORLD_WIDTH, WORLD_HEIGHT);
	player = new Player("images/flying-saucer.png", 50, 150);

	// Create a red circle that will move in a rectangular pattern
	enemy = new Player("images/other-saucer.png", 200, 200);
	enemy->move(0, -1);

	camera->observe(enemy);
	camera->observe(player);

	camera->follow(player);

//	atexit(SDL_Quit);
}

Manager::~Manager() {
	SDL_Quit();

//	if (screen != NULL) { delete screen; }
	if (world != NULL) { delete world; }
	if (camera != NULL) { delete camera; }
	if (player != NULL) { delete player; }
	if (enemy != NULL) { delete enemy; }
}

void Manager::handle_keydown(const SDLKey& key) {
	switch(key) {
	case SDLK_UP:
		yVel = 1;
		player->move(xVel, yVel);
		break;
	case SDLK_DOWN:
		yVel = -1;
		player->move(xVel, yVel);
		break;
	case SDLK_RIGHT:
		xVel = 1;
		player->move(xVel, yVel);
		break;
	case SDLK_LEFT:
		xVel = -1;
		player->move(xVel, yVel);
		break;
	case SDLK_q:
		done = true;
	case SDLK_SPACE:
		// If the player is currently being followed, follow the enemy.
		if (camera->getFollowedPlayer() == player) {
			camera->follow(enemy);
			std::cout << "Now following enemy." << std::endl;
		}
		// If the enemy is currently being followed, follow the player.
		else if (camera->getFollowedPlayer() == enemy) {
			camera->follow(player);
			std::cout << "Now following player." << std::endl;
		}
	default:
		break;
	}
}

void Manager::handle_keyup(const SDLKey& key) {
	switch(key) {
	case SDLK_UP:
		yVel = 0 ;
		player->move(xVel, yVel);
		break;
	case SDLK_DOWN:
		yVel = 0;
		player->move(xVel, yVel);
		break;
	case SDLK_RIGHT:
		xVel = 0;
		player->move(xVel, yVel);
		break;
	case SDLK_LEFT:
		xVel = 0;
		player->move(xVel, yVel);
		break;
	default:
		break;
	}
}

void Manager::move_enemy() {
	int padding_size = 110;
	// If the enemy reaches the bottom pad, turn right.
	if (enemy->getY() > world->getHeight() - padding_size && enemy->getYSpeed() > 0) {
		enemy->move(1, 0);
	}
	// If the enemy reaches the top pad, turn left.
	if (enemy->getY() < padding_size && enemy->getYSpeed() < 0) {
		enemy->move(-1, 0);
	}

	// If the enemy reaches the right pad, turn up.
	if (enemy->getX() > world->getWidth() - padding_size && enemy->getXSpeed() > 0) {
		enemy->move(0, 1);
	}
	// If the enemy reaches the left pad, turn down.
	if (enemy->getX() < padding_size && enemy->getXSpeed() < 0) {
		enemy->move(0, -1);
	}
}

void Manager::play() {
	SDL_Event event;
	cur_ticks = SDL_GetTicks();

	done = false;
	bool pause = false;
	unsigned int tick_sum = 0;
	while (!done) {
		prev_ticks = cur_ticks;
		cur_ticks = SDL_GetTicks();
		ticks = cur_ticks - prev_ticks;
		tick_sum += ticks;

		if (!pause) {
			camera->snapshot(screen, ticks);
		}

		SDL_Flip(screen);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				done = true;
				break;
			case SDL_KEYDOWN:
				handle_keydown(event.key.keysym.sym);
				break;
			case SDL_KEYUP:
				handle_keyup(event.key.keysym.sym);
				break;
			default:
				break;
			}
		}
		move_enemy();
	}
}
