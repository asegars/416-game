/*
 * Manager.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <SDL/SDL.h>
#include <string>
#include <sstream>
#include <iostream>
#include "Manager.h"
#include "FontLibrary.h"
#include "TextWriter.h"

#define WORLD_WIDTH 	800
#define WORLD_HEIGHT 	600

Manager::Manager() {
	screen = SDL_SetVideoMode(WORLD_WIDTH, WORLD_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::string("Unable to initialize SDL: ");
	}
	if (screen == NULL) {
		throw std::string("Unable to set video mode!");
	}

	world = new World("images/background-full.png");
	camera = new Camera(world, WORLD_WIDTH, WORLD_HEIGHT);
	player = new Player("images/heros.png", 50, WORLD_HEIGHT - 50);
	fontLibrary = FontLibrary::getInstance();
  loadHero();

	// Create a red circle that will move in a rectangular pattern
	enemy = new Enemy("images/other-saucer.png", 200, 200);
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

  heroSprites->~vector<Sprite*>();
}

void Manager::loadHero() {
  heroSprites = new vector<Sprite*>;
  heroSprites->push_back( new Sprite(0, 0, 12, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(12, 0, 36, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(48, 0, 35, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(83, 0, 22, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(105, 0, 37, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(142, 0, 33, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(175, 0, 25, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(388, 0, 12, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(352, 0, 36, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(317, 0, 35, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(295, 0, 22, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(258, 0, 37, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(225, 0, 33, 48, player->getPlayer()));
  heroSprites->push_back( new Sprite(200, 0, 25, 48, player->getPlayer()));
  player->setSprites(heroSprites);
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
	TextWriter writer;
	cur_ticks = SDL_GetTicks();
	Uint32 start_ticks = cur_ticks;

	done = false;
	bool pause = false;
	unsigned int tick_sum = 0;
	unsigned int frameCount = 0;

	std::stringstream outputStream;

	while (!done) {
		prev_ticks = cur_ticks;
		cur_ticks = SDL_GetTicks();
		ticks = cur_ticks - prev_ticks;
		tick_sum += ticks;

		if (!pause) {
			camera->snapshot(screen, ticks);

			// Print the runtime & framerate
			outputStream << "Sec: " << (cur_ticks - start_ticks) * .001;
			writer.write(outputStream.str().c_str(), screen, 650, 50);
			outputStream.str("");

			outputStream << "FPS: " << frameCount / ((cur_ticks - start_ticks) * .001);
			writer.write(outputStream.str().c_str(), screen, 650, 70);
			outputStream.str("");
		}

		SDL_Flip(screen);
		++frameCount;
   
    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if(event.type == SDL_QUIT)
      done = true;
    if(event.type == SDL_KEYDOWN && keystate[SDLK_ESCAPE]) 
      done = true;
    if(event.type == SDL_KEYDOWN && keystate[SDLK_q])
      done = true;

    if (keystate[SDLK_LEFT])
      player->decrSpeedX();
    if (keystate[SDLK_RIGHT])
      player->incrSpeedX();
    /* if (keystate[SDLK_UP])
      player->decrSpeedY();
    if (keystate[SDLK_DOWN])
      player->incrSpeedY(); */
    if (keystate[SDLK_SPACE] && !player->isFalling())
      player->jump();
    if (!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT] && !player->isFalling())
      player->decelX();
    /* if (!keystate[SDLK_UP] && !keystate[SDLK_DOWN])
      player->decelY(); */
    if(player->isFalling())
      player->decelY();

		move_enemy();
	}
}
