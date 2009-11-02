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
	SDL_Rect srcBounds, destBounds;
	// Blit the world
	Sprite* worldSprite = world->getSprite();
	srcBounds.x = cameraX / 2.2;
	srcBounds.y = 0;//cameraY;
	srcBounds.w = 0;//viewWidth;
	srcBounds.h = 0;//viewHeight;

	destBounds.x = 0;
	destBounds.y = viewHeight - background->getHeight();
	destBounds.w = 0;
	destBounds.h = 0;
	SDL_BlitSurface(worldSprite->getSurface(), &srcBounds, screen, NULL);

	// If the item that was just updated is what's being tracked,
	// readjust the camera location.
	relocate();

	srcBounds.x = float(cameraX);// / 2.2;
	srcBounds.y = cameraY;//0;
	srcBounds.w = viewWidth;//background->getWidth();
	srcBounds.h = viewHeight;//background->getHeight();
	destBounds.y = 0;//viewHeight - background->getHeight();
	SDL_BlitSurface(background->getSprite()->getSurface(), &srcBounds, screen,
			&destBounds);

	// If the item that was just updated is what's being tracked,
	// readjust the camera location.
	relocate();

	unsigned int i = 0;
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
		++i;
	}

//	SDL_Rect terrainSrcBounds = { cameraX, cameraY, viewWidth, viewHeight };
//	SDL_Rect terrainDestBounds = { 0, 0, 0, 0 };
//	SDL_BlitSurface(world->getSurface(), &terrainSrcBounds, screen, &terrainDestBounds);
}

void Camera::observe(Drawable* item) {
	subjects.push_back(item);
}

void Camera::setX(int x) {
	std::cout << x << std::endl;
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
