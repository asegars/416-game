/*
 * Enemy.cpp
 *
 *  Created on: Oct 25, 2009
 *      Author: luke
 */

#include "Enemy.h"
#include "Manager.h"

Enemy::Enemy(Sprite* spr) :
	sprite(spr), xMovement(0), yMovement(0), xSpeed(0), ySpeed(0), 
  loadedSprite(false) {}

Enemy::Enemy(std::string filename, float xw, float yw) :
	sprite(new Sprite(filename)), x(xw), y(yw), xMovement(0), yMovement(0),
	xSpeed(0), ySpeed(0), loadedSprite(true) {}

Enemy::~Enemy() {
	if (loadedSprite) {
		delete sprite;
	}
}

void Enemy::updatePosition(Uint32 ticks) {
	float height = static_cast<float> (sprite->getHeight());
	// Cap the player's motion if they are trying to move off of the
	//   left border of the world.
	if (y < 0 && ySpeed < 0) {
		ySpeed = 0;
	}
	// Cap the player's motion if they are trying to move off of the
	//   right border of the world.
	if (y > Manager::getInstance()->getWorld()->getHeight() - height && ySpeed > 0) {
		ySpeed = 0;
	}
	float incr = ySpeed * static_cast<float> (ticks) * 0.001;
	y += incr;

	float width = static_cast<float> (sprite->getWidth());
	// Cap the player's motion if they are trying to move off of the
	//   top  border of the world.
	if (x < 0 && xSpeed < 0) {
		xSpeed = 0;
	}
	// Cap the player's motion if they are trying to move off of the
	//   bottom border of the world.
	if (x > Manager::getInstance()->getWorld()->getWidth() - width && xSpeed > 0) {
		xSpeed = 0;
	}
	incr = xSpeed * static_cast<float> (ticks) * 0.001;
	x += incr;
}

void Enemy::move(int moveX, int moveY) {
	// Adjust the x speed depending on the keypress
	if (moveX > 0) {
		xSpeed = playerSpeed;
	} else if (moveX < 0) {
		xSpeed = -1 * playerSpeed;
	} else {
		xSpeed = 0;
	}

	// Adjust the y speed depending on the keypress
	if (moveY > 0) {
		ySpeed = -1 * playerSpeed;
	} else if (moveY < 0) {
		ySpeed = playerSpeed;
	} else {
		ySpeed = 0;
	}
}
