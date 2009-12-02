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

#define WORLD_WIDTH 	640
#define WORLD_HEIGHT 	480

#define NUM_ENEMIES   	4

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
		player = new Player("hero.bmp", 400, 2920);

		enemy = new Enemy("heckran.bmp", 0, 0, ENEMY_SPEED);
		fontLibrary = FontLibrary::getInstance();
		loadHero();
		loadEnemies();

		world->assignPlayer(player);
		for (unsigned int i = 0; i < enemies.size(); ++i) {
			world->addEnemy(enemies[i]);
		}

		victory = false;
		defeat = false;
		playerScore = 0;
    health = 100;

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
    if(i < 2)
		  enemies.push_back(new Enemy("heckran.bmp", (rand() % 250), 2922, 
        (rand() % ENEMY_SPEED + 50)));
    else
      enemies.push_back(new Enemy("heckran.bmp", (rand() % 250 + 550), 2922,
        (rand() % ENEMY_SPEED + 50)));
    enemies.at(i)->playerToAttack(player);
		enemies.at(i)->setSprites(enemySprites);
	}
}

int Manager::getScore() {
	if (!defeat && !victory) {
		playerScore += ticks * 0.1;
	}
	return playerScore;
}

void Manager::play() {
	SDL_Event event;
	TextWriter writer;
	cur_ticks = SDL_GetTicks();
	Uint32 start_ticks = cur_ticks;

	done = false;
  stopped = false;
	bool pause = false;
  float hitTimer = 0.0;
	float fireTimer = 1000.0;
	float fireDir = 0.0;
	unsigned int tick_sum = 0;
	float frames = 0.0;

	std::stringstream outputStream;

	camera->setScrollDelay(10000);

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
			camera->snapshot(screen, ticks);

			///////
			// Write text to the screen
			///////
			writer.switchFont(AGENT);
			writer.switchSize(32);
			outputStream << getScore();
			writer.write(outputStream.str().c_str(), screen, 300, 25);
			outputStream.str("");

			writer.switchFont(FREE_SANS);
			writer.switchSize(16);
			// Print the runtime & new framerate
			outputStream << "Sec: " << (cur_ticks - start_ticks) * .001;
			writer.write(outputStream.str().c_str(), screen, 485, 15);
			outputStream.str("");

			outputStream << "FPS: " << frames / ((cur_ticks - start_ticks) * .001);
			writer.write(outputStream.str().c_str(), screen, 485, 35);
			outputStream.str("");

      if(frames / ((cur_ticks - start_ticks) * .001) < 50)
        player->setJump(300);
      else if(frames / ((cur_ticks - start_ticks) * .001) >  100)
        player->setJump(600);
      else
        player->setJump(450);
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

		if (fireTimer > 450 && !defeat) {
			if (keystate[SDLK_LEFT])
				player->decrSpeedX();
			if (keystate[SDLK_RIGHT])
				player->incrSpeedX();
			if (keystate[SDLK_UP] && !player->isFalling())
				player->jump();
      // Can only fire once every 2 seconds... it's a big gun
			if (keystate[SDLK_SPACE] && !player->isFalling() && fireTimer > 2000) {
				fireDir = player->getXSpeed();
				player->setXSpeed(0.0);
				player->fire((player->isFacingRight()) ? 250.0 : -250.0, 0);
				fireTimer = 0.0;
			}
			if (!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT]
					&& !player->isFalling())
				player->decelX();
		}
		if (player->isFalling()) {
			player->decelY();
		}

    if(!defeat)
		  checkDeathConditions();

		if (victory && !stopped) {
			// Proceed to the next level?
			// Display something on screen?
			std::cout << "You win!" << std::endl;
      stopped = true;
		}

		if (defeat && !stopped) {
			// Stop the camera movement?
			// Display something on screen?
			std::cout << "Sorry, you lose!" << std::endl;
			camera->setScrollRate(0.0);
			player->setVisible(false);
      stopped = true;
		}
	}
}

void Manager::checkDeathConditions() {
	// Check to see if the player drowned.
	if (player->getY() > camera->getY() + camera->getHeight()) {
    std::cout << "You have drowned..." << std::endl;
		reportDefeat();
	}

	// Check to see if the player has been killed by a monster.
  if (world->playerCollision()) {
    if(health > 0)
      health -= 2;
	  std::cout << "You've been mauled!  Remaining Health: " << health 
      << std::endl;
    playerScore -= 10;
  }

  if(health <= 0) {
    reportDefeat();
    std::cout << "You've been killed..." << std::endl;
  }

}
