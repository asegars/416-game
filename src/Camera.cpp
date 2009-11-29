/*
 * Camera.cpp
 *
 *  Created on: Oct 6, 2009
 */
#include <iostream>
#include <sstream>
#include <cmath>
#include "Camera.h"
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
	playerCollision = false;
}

Camera::~Camera() {
}

/**
 * Relocates the camera to point higher and higher as time progresses.
 */
void Camera::relocate(unsigned int ticks) {
	// TODO: Test this on other systems.  Will the camera scroll at
	//   an acceptable rate?
	float scroll_rate = .03;
	cameraY = cameraY - round(scroll_rate * ticks);
	int highYlimit = world->getHeight();

	if (cameraY < 0) {
		cameraY = 0;
	}
	if (cameraY > highYlimit) {
		cameraY = highYlimit;
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
	srcBounds.x = cameraX; // / 2.2;
	srcBounds.y = cameraY; // / 2.2;
	srcBounds.w = viewWidth;
	srcBounds.h = viewHeight;

	destBounds.x = 0;
	destBounds.y = 0;
	destBounds.w = 0;
	destBounds.h = 0;
	SDL_BlitSurface(worldSprite->getSurface(), &srcBounds, screen, NULL);

	/*
	srcBounds.x = cameraX;
	srcBounds.y = cameraY;
	srcBounds.w = viewWidth;
	srcBounds.h = viewHeight;

	destBounds.x = 0;
	destBounds.y = 0;
//	SDL_BlitSurface(background->getSprite()->getSurface(), &srcBounds, screen,
//			&destBounds);
 */
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
			if(playerCount == 0 && playerCollision) {
				writer.write("I've been hit!", screen, destBounds.x - 30,
						destBounds.y - 20);
						outputStream.str("");
			}

			SDL_BlitSurface(sprite->getSurface(), &srcBounds, screen, &destBounds);
		}
		++iter;
		++playerCount;
	}
}

void Camera::snapshot(SDL_Surface* screen, Uint32 ticks) {
	// If the item that was just updated is what's being tracked,
	// readjust the camera location.
	if (SDL_GetTicks() > delayScroll) {
		relocate(ticks);
	}

	blitWorld(screen);
	blitDrawables(screen, ticks);
	blitTerrain(screen);
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

void Camera::setCollision(bool indicator) {
	playerCollision = indicator;
}
