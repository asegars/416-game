/*
 * Camera.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <iostream>
#include <cmath>
#include "Camera.h"
#include "terrain/Terrain.h"
#include "terrain/SolidTerrain.h"

Camera::Camera(World* world, Background* back, unsigned int width,
		unsigned int height) :
	cameraX(0), cameraY(0) {
	this->world = world;
	this->background = back;
	viewWidth = width;
	viewHeight = height;
}

Camera::~Camera() {
}

void Camera::relocate() {
	cameraX = tracker->getX() - (viewWidth / 2);
	cameraY = tracker->getY() - (viewHeight / 2);

	// Compute the upper bounds of the camera location
	int highXlimit = world->getWidth() - viewWidth;
	int highYlimit = world->getHeight() - viewHeight;

	// Check the bounds
	if (cameraX < 0) {
		cameraX = 0;
	}
	if (cameraX > highXlimit) {
		cameraX = highXlimit;
	}
	if (cameraY < 0) {
		cameraY = 0;
	}
	if (cameraY > highYlimit) {
		cameraY = highYlimit;
	}

}

void Camera::follow(Player* player) {
	tracker = player;
}

void Camera::snapshot(SDL_Surface* screen, Uint32 ticks) {
	// If the item that was just updated is what's being tracked,
	// readjust the camera location.
	relocate();

	SDL_Rect srcBounds, destBounds;
	// Blit the world
	Sprite* worldSprite = world->getSprite();
	srcBounds.x = cameraX / 2.2;
	srcBounds.y = cameraY / 2.2;
	srcBounds.w = viewWidth;
	srcBounds.h = viewHeight;

	destBounds.x = 0;
	destBounds.y = 0;
	destBounds.w = 0;
	destBounds.h = 0;
	SDL_BlitSurface(worldSprite->getSurface(), &srcBounds, screen, &destBounds);

	srcBounds.x = cameraX;
	srcBounds.y = cameraY;
	srcBounds.w = viewWidth;
	srcBounds.h = viewHeight;

	destBounds.x = 0;
	destBounds.y = 0;//viewHeight - background->getHeight();
	SDL_BlitSurface(background->getSprite()->getSurface(), &srcBounds, screen,
			&destBounds);

	// If the item that was just updated is what's being tracked,
	// readjust the camera location.
	relocate();

	// Blit each drawable figure onto the world.
	std::vector<Drawable *>::const_iterator iter = subjects.begin();
	while (iter != subjects.end()) {
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

		SDL_BlitSurface(sprite->getSurface(), &srcBounds, screen, &destBounds);
		++iter;
	}

	WorldMap* map = world->getMap();
	int cellDim = map->getCellDim();
	SDL_Rect terrainBounds = {0, 0, cellDim, cellDim};
	for (int height = 0; height < map->getCellHeight(); ++height) {
		for (int width = 0; width < map->getCellWidth(); ++width) {
			int realX = width * cellDim;
			int realY = height * cellDim;

			// Convert from world coords to camera coords
			SDL_Rect terrainPos = {realX - cameraX, realY - cameraY, 0, 0};
			// If the cell has terrain in it, blit it
			if (map->getCell(width, height) != NULL) {
				SDL_BlitSurface(map->getCell(width, height)->getSprite()->getSurface(),
						&terrainBounds,
						screen,
						&terrainPos);
			}
		}
	}
}

void Camera::observe(Drawable* item) {
	subjects.push_back(item);
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
