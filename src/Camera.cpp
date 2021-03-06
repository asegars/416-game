/*
 * Camera.cpp
 *
 *  Created on: Oct 6, 2009
 */
#include <iostream>
#include <sstream>
#include <cmath>
#include <ctime>
#include "Camera.h"
#include "Manager.h"
#include "terrain/Terrain.h"
#include "terrain/SolidTerrain.h"

Camera::Camera(World* world, Background* back, unsigned int width,
		unsigned int height) {
	this->world = world;
	this->background = back;
	viewWidth = width;
	viewHeight = height;

	cameraX = 0;
	cameraY = world->getHeight() - viewHeight;

	delayScroll = 0;
	waveHeight = 0;
	scrollRate = .02;
	alpha = 255;

	tracker = NULL;

	srand(time(NULL));
}

Camera::~Camera() {
}

/**
 * Relocates the camera to point higher and higher as time progresses.
 */
void Camera::relocate(unsigned int ticks) {
	float buffer = 250;
	// Only move the camera in the Y direction if the start delay has passed.
	if (SDL_GetTicks() > delayScroll) {
		// TODO: Test this on other systems.  Will the camera scroll at
		//   an acceptable rate?
		cameraY = cameraY - (scrollRate * ticks);
		int highYlimit = world->getHeight();

		if (cameraY < 0) {
			cameraY = 0;
		}
		if (cameraY > highYlimit) {
			cameraY = highYlimit;
		}

		// Scroll the waves up as well.
		if (waveHeight < 1) {
			waveHeight += (ticks * .0001);
		}
		else {
			waveHeight = 1;
		}
	}
	// The camera can always move in the X direction -- this is player-dependent.
	if (tracker->getX() + tracker->getWidth() + buffer > cameraX + viewWidth) {
		cameraX += 2;
		//std::cout << "Moving camera right to " << cameraX << std::endl;
	}
	if (tracker->getX() - buffer < cameraX) {
		cameraX -= 2;
		//std::cout << "Moving camera left to " << cameraX << std::endl;
	}

	if (cameraX < 0) {
		cameraX = 0;
	}
	if (cameraX + viewWidth > world->getWidth()) {
		cameraX = world->getWidth() - viewWidth;
	}
}

// Returns true if the boundingBox (in CAMERA COORDINATES) is visible.
bool Camera::isVisible(SDL_Rect& boundingBox) {
	// Too far to the left
	if (boundingBox.x + boundingBox.w < 0) return false;
	// Too far to the right
	if (boundingBox.x > viewWidth) return false;
	// Too far up
	if (boundingBox.y + boundingBox.h < 0) return false;
	// Too far down
	if (boundingBox.y > viewHeight) return false;

	return true;
}


void Camera::blitWorld(SDL_Surface* screen) {
	SDL_Rect srcBounds, destBounds;

	// Blit the world
	Sprite* worldSprite = world->getSprite();
	srcBounds.x = cameraX / 2.0;
	srcBounds.y = cameraY / 2.0;
	srcBounds.w = viewWidth;
	srcBounds.h = viewHeight;

	destBounds.x = 0;
	destBounds.y = 0;
	destBounds.w = 0;
	destBounds.h = 0;
	SDL_BlitSurface(worldSprite->getSurface(), &srcBounds, screen, NULL);
}

void Camera::blitTerrain(SDL_Surface* screen) {
	std::list<Terrain *> terrain = world->getMap()->getMap();
	int cellDim = world->getMap()->getCellDim();

	std::list<Terrain *>::const_iterator iter = terrain.begin();
	SDL_Rect terrainBounds = {0, 0, cellDim, cellDim};
	SDL_Rect terrainPos = {0, 0, cellDim, cellDim};
	while (iter != terrain.end()) {
		terrainPos.x = (*iter)->getX() - cameraX;
		terrainPos.y = (*iter)->getY() - cameraY;

		if (isVisible(terrainBounds)) {
			SDL_BlitSurface((*iter)->getSprite()->getSurface(),
					&terrainBounds,
					screen,
					&terrainPos);
		}
		++iter;
	}
}

void Camera::blitDrawables(SDL_Surface* screen, unsigned int ticks) {
	SDL_Rect srcBounds, destBounds;
  TextWriter writer;
  std::stringstream outputStream;

  std::list<Drawable *> drawables = world->getDrawables();

  unsigned int playerCount = 0;
	// Blit each drawable figure onto the world.
	std::list<Drawable *>::const_iterator iter = drawables.begin();
	while (iter != drawables.end()) {
		(*iter)->updatePosition(ticks);

		if ((*iter)->isVisible()) {
			Sprite* sprite = (*iter)->getSprite();
			unsigned int x = (*iter)->getX();
			unsigned int y = (*iter)->getY();

			srcBounds.x = sprite->getPosX();
			srcBounds.y = sprite->getPosY();
			srcBounds.w = sprite->getWidth();
			srcBounds.h = sprite->getHeight();
			destBounds.x = x - cameraX;
			destBounds.y = y - cameraY;
			destBounds.w = srcBounds.w;
			destBounds.h = srcBounds.h;

			if (isVisible(destBounds)) {
				// TODO: This probably needs to be moved somewhere else...
				if (playerCount == 0 && world->playerCollision()) {
					writer.write("I've been hit!", screen, destBounds.x - 30,
						destBounds.y - 20);
						outputStream.str("");
				}

				SDL_BlitSurface(sprite->getSurface(), &srcBounds, screen, &destBounds);
			}
		}
		++iter;
		++playerCount;
	}
}

void Camera::blitWaves(SDL_Surface* screen) {
	std::vector<Sprite *> waves = world->getWaves();

	int xLoc, width;
	SDL_Rect srcBounds;
	SDL_Rect destBounds;

	srcBounds.y = 0;
	srcBounds.w = viewWidth;

	destBounds.x = 0;

	for (unsigned int i = 0; i < waves.size(); ++i) {
		xLoc = waves[i]->getPosX();
		width = waves[i]->getWidth();

		srcBounds.h = waveHeight * waves[i]->getHeight();
		destBounds.y = viewHeight - srcBounds.h;

		// if the wave is moving right, move the wave unless its gone too far.
		//   then reverse it and move it the other direction.
		if (world->getWaveDirection(i) > 0) {
			// If the wave scrolls too far, turn it around.
			if (xLoc > width - viewWidth) { //width - xLoc < viewWidth) {
				world->setWaveDirection(i, - (rand() % 100 + 50) / 50);
			}
			waves[i]->setPosX(waves[i]->getPosX() + world->getWaveDirection(i));
		}
		else {
			// If the wave scrolls too far, turn it around.
			if (xLoc <= 0) {
				world->setWaveDirection(i, (rand() % 100 + 50) / 50);
			}
			waves[i]->setPosX(waves[i]->getPosX() + world->getWaveDirection(i));
		}

		srcBounds.x = waves[i]->getPosX();
		// blit the wave
		SDL_BlitSurface(waves[i]->getSurface(), &srcBounds, screen, &destBounds);
	}
}

void Camera::snapshot(SDL_Surface* screen, Uint32 ticks) {
	if (tracker == NULL) {
		tracker = Manager::getInstance()->getPlayer();
	}
	// If the item that was just updated is what's being tracked,
	// readjust the camera location.
	relocate(ticks);


	blitWorld(screen);
	blitDrawables(screen, ticks);
	blitTerrain(screen);
	blitWaves(screen);
}

void Camera::setX(int x) {
	if (x < 0) {
		x = 0;
		return;
	}
	if (x > viewWidth) {
		x = viewWidth;
		return;
	}

	cameraX = x;
}

void Camera::setY(int y) {
	if (y < 0) {
		y = 0;
		return;
	}
	if (y > viewHeight) {
		y = viewHeight;
		return;
	}

	cameraY = y;
}
