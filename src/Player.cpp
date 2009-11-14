/*
 * Player.cpp
 *
 *  Created on: Oct 5, 2009
 */

#include <iostream>
#include <cmath>
#include "Player.h"
#include "Manager.h"

Player::Player(Sprite* spr) :
	sprite(spr), loadedSprite(false) {
	x = 0;
	y = 48;

	xSpeed = 0;
	ySpeed = 0;
}

Player::Player(std::string filename, float xw, float yw) : Character(),
	sprite(new Sprite(filename)), loadedSprite(true), falling(true) {
	x = xw;
	y = yw;
	xSpeed = 0;
	ySpeed = 0;
}

Player::~Player() {
	if (sprite != NULL) { delete sprite; }
//	if (sprites != NULL) { delete sprites; }
}

void Player::setSprites(vector<Sprite*> &s) {
//  sprites = new vector<Sprite*>;
  for(unsigned int i = 0; i < s.size(); ++i) {
    sprites.push_back(s.at(i));
  }
  curSprite = 0;
  interval = 0;
  fireInterval = 0;
}

void Player::updatePosition(Uint32 ticks) {
	float height = static_cast<float> (sprites.at(curSprite)->getHeight());
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
	float yIncr = ySpeed * static_cast<float> (ticks) * 0.001;

	float width = static_cast<float> (sprites.at(curSprite)->getWidth());
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
	float xIncr = xSpeed * static_cast<float> (ticks) * 0.001;

	// If the player isn't colliding with terrain, proceed like normal.
	if (!collidesWithWorld(xIncr, yIncr)) {
		x += xIncr;
		y += yIncr;
	}
	else {
		if (!collidesWithWorld(xIncr, 0)) {
			x += xIncr;
		}
		if (collidesWithWorld(0, yIncr)) {
			if (yIncr > 0) falling = false;
			else ySpeed = -ySpeed;
		}
	}

  if(!justFired)
    advanceFrame(ticks);
  else
    advanceFireFrame(ticks);
}
void Player::advanceFireFrame(Uint32 ticks) {
  fireInterval += ticks;

  if(curFrame == 0)
    fireDir = 1;
  
  if(fireDir > 0) {
    if(fireInterval < 150)
      curFrame = 14;
    else if(fireInterval < 300)
      curFrame = 15;
    else
      curFrame = 16;
  }
  else {
    if(fireInterval < 150)
      curFrame = 17;
    else if(fireInterval < 300)
      curFrame = 18;
    else
      curFrame = 19; 
  }

  if(fireInterval > 450) {
    justFired = false;
    fireInterval = 0;
    if(fireDir > 0)
      curFrame = 0;
    else
      curFrame = 7;
  }
}


void Player::advanceFrame(Uint32 ticks) {
  interval += ticks;
  if (fabs(interval * xSpeed) > 15000 && xSpeed > 0) {   
    curFrame = (++curFrame) % (frames->size()/2);
    if(curFrame > 6 || curFrame == 0)
      curFrame = 1;
    interval = 0;
  }
  else if (fabs(interval * xSpeed) > 15000 && xSpeed < 0) { 
    curFrame = (++curFrame) % (frames->size());
    if(curFrame < 8 || curFrame > 13)
      curFrame = 8;
    interval = 0;
  }
  else if (xSpeed == 0) {
    if(curFrame < 7)
      curFrame = 0;
    else
      curFrame = 7;
  }
}

void Player::incrSpeedX() {
  if(xSpeed < MAX_SPEED && !falling)
    xSpeed += 10;
  else if(xSpeed < MAX_SPEED && (abs(xSpeed) > 20))
    xSpeed += 2;
}

void Player::decrSpeedX() {
  if(xSpeed > -MAX_SPEED && !falling)
    xSpeed -= 10;
  else if(xSpeed > -MAX_SPEED && (abs(xSpeed) > 20))
    xSpeed -= 2;
}


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
