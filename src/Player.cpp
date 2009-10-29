/*
 * Player.cpp
 *
 *  Created on: Oct 5, 2009
 *      Author: luke
 */

#include <iostream>
#include <cmath>
#include "Player.h"
#include "Manager.h"

Player::Player(Sprite* spr) :
	sprite(spr), xMovement(0), yMovement(0), xSpeed(0), ySpeed(0), 
  loadedSprite(false) { interval = 0; }

Player::Player(std::string filename, float xw, float yw) :
	sprite(new Sprite(filename)), x(xw), y(yw), xMovement(0), yMovement(0),
	xSpeed(0), ySpeed(0), loadedSprite(true), falling(true) { interval = 0; }

Player::~Player() {
	if (loadedSprite) {
		delete sprite;
	}
}

void Player::setSprites(vector<Sprite*> *s) {
  sprites = new vector<Sprite*>;
  for(unsigned int i = 0; i < s->size(); ++i) {
    sprites->push_back(s->at(i));
  }
  curSprite = 0;
}

void Player::updatePosition(Uint32 ticks) {
	float height = static_cast<float> (sprites->at(curSprite)->getHeight());
	// Cap the player's motion if they are trying to move off of the
	//   top  border of the world.
	if (y <= 0 && ySpeed < 0) {
		ySpeed = 0;
	}
	// Cap the player's motion if they are trying to move off of the
	//   bottom border of the world.
	if (y >= Manager::getInstance()->getWorld()->getHeight() - height && ySpeed > 0) {
		ySpeed = 0;
    y = Manager::getInstance()->getWorld()->getHeight() - height;
    falling = false;
	}
	float incr = ySpeed * static_cast<float> (ticks) * 0.001;
	y += incr;

	float width = static_cast<float> (sprites->at(curSprite)->getWidth());
	// Cap the player's motion if they are trying to move off of the
	//   left border of the world.
	if (x <= 0 && xSpeed < 0) {
		xSpeed = 0;
	}
	// Cap the player's motion if they are trying to move off of the
	//   right border of the world.
	if (x >= Manager::getInstance()->getWorld()->getWidth() - width && xSpeed > 0) {
		xSpeed = 0;
	}
	incr = xSpeed * static_cast<float> (ticks) * 0.001;
	x += incr;
  advanceFrame(ticks);
}

void Player::advanceFrame(Uint32 ticks) {
  interval += ticks;
  if (fabs(interval * xSpeed) > 15000 && xSpeed > 0) {   
    curSprite = (++curSprite) % (sprites->size()/2);
    if(curSprite > 6 || curSprite == 0)
      curSprite = 1;
    interval = 0;
  }
  else if (fabs(interval * xSpeed) > 15000 && xSpeed < 0) { 
    curSprite = (++curSprite) % (sprites->size());
    if(curSprite < 8 || curSprite == 0)
      curSprite = 8;
    interval = 0;
  }
  else if (xSpeed == 0) {
    if(curSprite < 7)
      curSprite = 0;
    else
      curSprite = 7;
  }
}

void Player::incrSpeedX() {
  if(xSpeed < MAX_SPEED && !falling)
    xSpeed += 10;
}

void Player::decrSpeedX() {
  if(xSpeed > -MAX_SPEED && !falling)
    xSpeed -= 10;
}

/*
void Player::incrSpeedY() {
  if(ySpeed < MAX_SPEED && !falling)
    ySpeed += 10;
}

void Player::decrSpeedY() {
  if(ySpeed > -MAX_SPEED && !falling)
    ySpeed -= 10;
}
*/

void Player::decelX() {
  if(xSpeed != 0 && (abs(xSpeed) > 10))
    xSpeed *= DECEL;
  else
    xSpeed = 0;
}

// decelY() is only called when after a player jumps
void Player::decelY() {
    ySpeed += 10;
}

void Player::jump() {
  if (!falling) {
    ySpeed = -MAX_JUMP;
    falling = true;
  }
}

void Player::move(int moveX, int moveY) {
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
