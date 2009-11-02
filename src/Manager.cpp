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
#include <time.h>
#include "Manager.h"
#include "FontLibrary.h"
#include "terrain/SolidTerrain.h"
#include "TextWriter.h"

#define WORLD_WIDTH 	800
#define WORLD_HEIGHT 	600
#define NUM_ENEMIES   5

Manager::Manager() {
	screen = SDL_SetVideoMode(WORLD_WIDTH, WORLD_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::string("Unable to initialize SDL: ");
	}
	if (screen == NULL) {
		throw std::string("Unable to set video mode!");
	}

  	srand(time(NULL));
	world = new World("images/background1.png");
  	background = new Background();
	camera = new Camera(world, background, WORLD_WIDTH, WORLD_HEIGHT);
	player = new Player("images/heros.png", 50, 400);
	enemy = new Enemy("images/heckran.png", 0, 0);
	fontLibrary = FontLibrary::getInstance();
	loadHero();
	loadEnemies();
	for(unsigned int i = 0; i < enemies.size(); ++i) {
	  camera->observe(enemies.at(i));
	}
	camera->observe(player);
	camera->follow(player);

}

// TODO: Fix segfault here.
Manager::~Manager() {
	std::cout << "Cleaning up...";
	if (world != NULL) { delete world; }
	if (background != NULL) { delete background; }
	if (camera != NULL) { delete camera; }
	if (player != NULL) { delete player; }
    if (enemy != NULL) { delete enemy; }
    if (fontLibrary != NULL) { delete fontLibrary; }

    for(unsigned int i = 0; i < heroSprites.size(); ++i) {
		if (heroSprites.at(i) != NULL) delete heroSprites.at(i);
	}

    for(unsigned int j = 0; j < enemySprites.size(); ++j) {
		if (enemySprites.at(j) != NULL) delete enemySprites.at(j);
	}

  	for(unsigned int k = 0; k < enemies.size(); ++k) {
  		if (enemies.at(k) != NULL) delete enemies.at(k);
  	}
	SDL_Quit();
  	std::cout << "done." << std::endl;
}

void Manager::loadHero() {
//  heroSprites = new vector<Sprite*>;
  heroSprites.push_back( new Sprite(0, 0, 12, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(12, 0, 36, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(48, 0, 35, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(83, 0, 22, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(105, 0, 37, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(142, 0, 33, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(175, 0, 25, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(388, 0, 12, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(352, 0, 36, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(317, 0, 35, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(295, 0, 22, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(258, 0, 37, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(225, 0, 33, 48, player->getPlayer()));
  heroSprites.push_back( new Sprite(200, 0, 25, 48, player->getPlayer()));
  player->setSprites(heroSprites);
}

void Manager::loadEnemies() {
//  enemySprites = new vector<Sprite*>;
  enemySprites.push_back( new Sprite(0, 0, 43, 48, enemy->getEnemy()));
  enemySprites.push_back( new Sprite(43, 0, 43, 48, enemy->getEnemy()));
  enemySprites.push_back( new Sprite(86, 0, 43, 48, enemy->getEnemy()));
  enemySprites.push_back( new Sprite(129, 0, 43, 48, enemy->getEnemy()));
  enemySprites.push_back( new Sprite(172, 0, 43, 48, enemy->getEnemy()));
  enemySprites.push_back( new Sprite(215, 0, 43, 48, enemy->getEnemy()));
  for(unsigned int i = 0; i < NUM_ENEMIES; ++i) {
    enemies.push_back(new Enemy("images/heckran.png", 
                                (rand() % 2400), 1152));
    enemies.at(i)->setSprites(enemySprites);
  }
}

bool Manager::collision() {

  float enemyWidth;
  float enemyHeight;
  float playerWidth = player->getWidth();
  float playerHeight = player->getHeight();
  
  for(unsigned int i = 0; i < enemies.size(); ++i) {
    Enemy *current = enemies.at(i);
    enemyWidth = current->getWidth();
    enemyHeight = current->getHeight();   
    if(current->getX() + enemyWidth - 2 < player->getX()) {
      continue;
    }
    if(current->getX() > player->getX() + playerWidth - 2) {
      continue;
    }
    if(current->getY() + enemyHeight - 2 < player->getY()) {
      continue;
    }
    if(current->getY() > player->getY() + playerHeight - 2) {
      continue;
    }
    return true;
  }
  
  return false;
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
      if(collision())
        camera->setCollision(true);
      else
        camera->setCollision(false);
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
    if (keystate[SDLK_SPACE] && !player->isFalling())
      player->jump();
    if (!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT] && !player->isFalling())
      player->decelX();
    if(player->isFalling())
      player->decelY();
	}
}
