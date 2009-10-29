/*
 * Camera.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <iostream>
#include "Camera.h"

Camera::Camera(World* world, unsigned int width, unsigned int height) : 
     cameraX(0), cameraY(0) {
	this->world = world;
	viewWidth = width;
	viewHeight = height;
}

Camera::~Camera() {
	//delete world;
}

void Camera::relocate() {
	cameraX = tracker->getX() - (viewWidth / 2);
	cameraY = tracker->getY() - (viewHeight / 2);

	// Compute the upper bounds of the camera location
	int highXlimit = world->getWidth() - viewWidth;
	int highYlimit = world->getHeight() - viewHeight;

	// Check the bounds
	if (cameraX < 0) { cameraX = 0; }
	if (cameraX > highXlimit) {
		cameraX = highXlimit;
	}
	if (cameraY < 0) { cameraY = 0; }
	if (cameraY > highYlimit) {
		cameraY = highYlimit;
	}

}

void Camera::follow(Player* player) {
	tracker = player;
}

void Camera::snapshot(SDL_Surface* screen, Uint32 ticks) {
	// Blit the world
	Sprite* worldSprite = world->getSprite();
	SDL_Rect srcBounds = {cameraX, cameraY, viewWidth, viewHeight};
	SDL_Rect destBounds = {0, 0, 0, 0};

	// If the item that was just updated is what's being tracked,
	//   readjust the camera location.
	relocate();

	SDL_BlitSurface(worldSprite->getSurface(), &srcBounds, screen, NULL);

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
		iter++;
	}
}

void Camera::observe(Drawable* item) {
	subjects.push_back(item);
}

void Camera::setX(int x) {
	std::cout << x << std::endl;
	if (x < 0) { x = 0; return; }
	if (x > viewWidth) { x = viewWidth; return; }

	cameraX = x;
}

void Camera::setY(int y) {
	if (y < 0) { y = 0; return; }
	if (y > viewHeight) { y = viewHeight; return; }

	cameraY = y;
}
