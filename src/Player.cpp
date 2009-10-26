/*
 * Player.cpp
 *
 *  Created on: Oct 5, 2009
 *      Author: luke
 */

#include <iostream>

#include "Player.h"
#include "Manager.h"

Player::Player(Sprite* spr) :
	sprite(spr), xMovement(0), yMovement(0), xSpeed(0), ySpeed(0), loadedSprite(false) {
}

Player::Player(std::string filename, float x, float y) :
	sprite(new Sprite(filename, x, y)), xMovement(0), yMovement(0),
	xSpeed(0), ySpeed(0), loadedSprite(true) {
}

Player::~Player() {
	if (loadedSprite) {
		delete sprite;
	}
}

void Player::updatePosition(Uint32 ticks) {
	float height = static_cast<float> (sprite->getHeight());
	// Cap the player's motion if they are trying to move off of the
	//   left border of the world.
	if (sprite->getY() < 0 && ySpeed < 0) {
		ySpeed = 0;
	}
	// Cap the player's motion if they are trying to move off of the
	//   right border of the world.
	if (sprite->getY() > Manager::getInstance()->getWorld()->getHeight() - height && ySpeed > 0) {
		ySpeed = 0;
	}
	float incr = ySpeed * static_cast<float> (ticks) * 0.001;
	sprite->setY(sprite->getY() + incr);

	float width = static_cast<float> (sprite->getWidth());
	// Cap the player's motion if they are trying to move off of the
	//   top  border of the world.
	if (sprite->getX() < 0 && xSpeed < 0) {
		xSpeed = 0;
	}
	// Cap the player's motion if they are trying to move off of the
	//   bottom border of the world.
	if (sprite->getX() > Manager::getInstance()->getWorld()->getWidth() - width && xSpeed > 0) {
		xSpeed = 0;
	}
	incr = xSpeed * static_cast<float> (ticks) * 0.001;
	sprite->setX(sprite->getX() + incr);
}

void Player::incrSpeedX() {
  if(xSpeed < MAX_SPEED)
    xSpeed += 10;
}

void Player::decrSpeedX() {
  if(xSpeed > -MAX_SPEED)
    xSpeed -= 10;
}

void Player::incrSpeedY() {
  if(ySpeed < MAX_SPEED)
    ySpeed += 10;
}

void Player::decrSpeedY() {
  if(ySpeed > -MAX_SPEED)
    ySpeed -= 10;
}

void Player::decelX() {
  if(xSpeed != 0 && (abs(xSpeed) > 10))
    xSpeed *= DECEL;
  else
    xSpeed = 0;
}

void Player::decelY() {
  if(ySpeed != 0 && (abs(ySpeed) > 10))
    ySpeed *= DECEL;
  else
    ySpeed = 0;
}

void Player::move(int x, int y) {
	// Adjust the x speed depending on the keypress
	if (x > 0) {
		xSpeed = playerSpeed;
	} else if (x < 0) {
		xSpeed = -1 * playerSpeed;
	} else {
		xSpeed = 0;
	}

	// Adjust the y speed depending on the keypress
	if (y > 0) {
		ySpeed = -1 * playerSpeed;
	} else if (y < 0) {
		ySpeed = playerSpeed;
	} else {
		ySpeed = 0;
	}
}
