/*
 * Manager.cpp
 *
 *  Created on: Oct 6, 2009
 */
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
#include <string>
#include <sstream>
#include <iostream>
#include <time.h>
#include "Manager.h"
#include "FontLibrary.h"
#include "terrain/SolidTerrain.h"
#include "resources/SoundManager.h"
#include "resources/GraphicManager.h"
#include "TextWriter.h"

#define WORLD_WIDTH 	800
#define WORLD_HEIGHT 	600

#define NUM_ENEMIES   	3

Manager::Manager() {
	try {
		screen = SDL_SetVideoMode(WORLD_WIDTH, WORLD_HEIGHT, 16, SDL_HWSURFACE
				| SDL_DOUBLEBUF);

		if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
			throw std::string("Unable to initialize SDL: ");
		}
		if (screen == NULL) {
			throw std::string("Unable to set video mode!");
		}

		srand(time(NULL));
		world = new World("waterfall.bmp");
		background = new Background();
		camera = new Camera(world, background, WORLD_WIDTH, WORLD_HEIGHT);
		player = new Player("hero.bmp", 50, 2920);

		enemy = new Enemy("heckran.bmp", 0, 0);
		fontLibrary = FontLibrary::getInstance();
		loadHero();
		loadEnemies();

		world->assignPlayer(player);
		for (unsigned int i = 0; i < enemies.size(); ++i) {
			world->addEnemy(enemies[i]);
		}
		std::cout << "Finished manager constructor" << std::endl;
	} catch (std::string e) {
		std::cerr << "Initialization exception: " << e << std::endl;
		exit(1);
	}
}

Manager::~Manager() {
	delete SoundManager::getInstance();
	delete GraphicManager::getInstance();

	if (world != NULL) {
		delete world;
	}
	if (background != NULL) {
		delete background;
	}
	if (camera != NULL) {
		delete camera;
	}
	if (player != NULL) {
		delete player;
	}
	if (enemy != NULL) {
		delete enemy;
	}
	if (fontLibrary != NULL) {
		delete fontLibrary;
	}

	for (unsigned int i = 0; i < heroSprites.size(); ++i) {
		if (heroSprites.at(i) != NULL)
			delete heroSprites.at(i);
	}

	for (unsigned int j = 0; j < enemySprites.size(); ++j) {
		if (enemySprites.at(j) != NULL)
			delete enemySprites.at(j);
	}

	for (unsigned int k = 0; k < enemies.size(); ++k) {
		if (enemies.at(k) != NULL)
			delete enemies.at(k);
	}
	SDL_Quit();
}

void Manager::loadHero() {
	//  heroSprites = new vector<Sprite*>;
	heroSprites.push_back(new Sprite(0, 0, 12, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(12, 0, 36, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(48, 0, 35, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(83, 0, 22, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(105, 0, 37, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(142, 0, 33, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(175, 0, 25, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(388, 0, 12, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(352, 0, 36, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(317, 0, 35, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(295, 0, 22, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(258, 0, 37, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(225, 0, 33, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(200, 0, 25, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(400, 0, 43, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(443, 0, 43, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(486, 0, 44, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(617, 0, 43, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(574, 0, 43, 48, player->getPlayer()));
	heroSprites.push_back(new Sprite(530, 0, 44, 48, player->getPlayer()));
	player->setSprites(heroSprites);
}

void Manager::loadEnemies() {
	//  enemySprites = new vector<Sprite*>;
	enemySprites.push_back(new Sprite(0, 0, 43, 48, enemy->getEnemy()));
	enemySprites.push_back(new Sprite(43, 0, 43, 48, enemy->getEnemy()));
	enemySprites.push_back(new Sprite(86, 0, 43, 48, enemy->getEnemy()));
	enemySprites.push_back(new Sprite(129, 0, 43, 48, enemy->getEnemy()));
	enemySprites.push_back(new Sprite(172, 0, 43, 48, enemy->getEnemy()));
	enemySprites.push_back(new Sprite(215, 0, 43, 48, enemy->getEnemy()));
	for (unsigned int i = 0; i < NUM_ENEMIES; ++i) {
		enemies.push_back(
				new Enemy("heckran.bmp", (rand() % 800), 2922));
		enemies.at(i)->setSprites(enemySprites);
	}
}

bool Manager::collision() {

	float enemyWidth;
	float enemyHeight;
	float playerWidth = player->getWidth();
	float playerHeight = player->getHeight();

	for (unsigned int i = 0; i < enemies.size(); ++i) {
		Enemy *current = enemies.at(i);
		enemyWidth = current->getWidth();
		enemyHeight = current->getHeight();
		if (current->getX() + enemyWidth - 5 < player->getX()) {
			continue;
		}
		if (current->getX() > player->getX() + playerWidth - 5) {
			continue;
		}
		if (current->getY() + enemyHeight - 5 < player->getY()) {
			continue;
		}
		if (current->getY() > player->getY() + playerHeight - 5) {
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
  float hitTimer = 0.0;
	float fireTimer = 1000.0;
	float fireDir = 0.0;
	unsigned int tick_sum = 0;
	float frames = 0.0;

	std::stringstream outputStream;

	camera->setScrollDelay(14100);

	SoundManager* soundManager = SoundManager::getInstance();
	Mix_Chunk* bgMusic = soundManager->load("background-music.wav");

	soundManager->play(bgMusic);

	while (!done) {
		prev_ticks = cur_ticks;
		cur_ticks = SDL_GetTicks();
		ticks = cur_ticks - prev_ticks;
		tick_sum += ticks;
    fireTimer += ticks;
    hitTimer += ticks;

		if (!pause) {
			if (collision()) {
				camera->setCollision(true);
				hitTimer = 0.0;
			}
			else if ((hitTimer * .001) > 1.5) {
				camera->setCollision(false);
			}
			camera->snapshot(screen, ticks);

			writer.switchFont(AGENT);
			writer.switchSize(32);
			outputStream << (cur_ticks - start_ticks) * .001;
			writer.write(outputStream.str().c_str(), screen, 325, 25);
			outputStream.str("");

			writer.switchFont(FREE_SANS);
			writer.switchSize(16);
			// Print the runtime & new Spriterate
			outputStream << "Sec: " << (cur_ticks - start_ticks) * .001;
			writer.write(outputStream.str().c_str(), screen, 600, 50);
			outputStream.str("");

			outputStream << "FPS: " << frames / ((cur_ticks - start_ticks) * .001);
			writer.write(outputStream.str().c_str(), screen, 600, 70);
			outputStream.str("");
		}

		SDL_Flip(screen);
		++frames;

		SDL_PollEvent(&event);
		Uint8 *keystate = SDL_GetKeyState(NULL);

		if (event.type == SDL_QUIT)
			done = true;
		if (event.type == SDL_KEYDOWN && keystate[SDLK_ESCAPE])
			done = true;
		if (event.type == SDL_KEYDOWN && keystate[SDLK_q])
			done = true;

		if (fireTimer > 450) {
			if (keystate[SDLK_LEFT])
				player->decrSpeedX();
			if (keystate[SDLK_RIGHT])
				player->incrSpeedX();
			if (keystate[SDLK_UP] && !player->isFalling())
				player->jump();
			if (keystate[SDLK_SPACE] && !player->isFalling() && fireTimer > 1000) {
				fireDir = player->getXSpeed();
				player->setXSpeed(0.0);
				player->fire((player->isFacingRight()) ? 160.0 : -160.0, 0);

				fireTimer = 0.0;
			}
			if (!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT]
					&& !player->isFalling())
				player->decelX();
		}
		if (player->isFalling())
			player->decelY();
	}
}
