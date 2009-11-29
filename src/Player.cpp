/*
 * Player.cpp
 *
 *  Created on: Oct 5, 2009
 */

#include <iostream>
#include <cmath>
#include "resources/SoundManager.h"
#include "Player.h"
#include "Character.h"
#include "World.h"
#include "Bullet.h"
#include "Manager.h"

Player::Player(Sprite* spr) :
	sprite(spr), loadedSprite(false), falling(true) {
	x = 0;
	y = 48;

	xSpeed = 0;
	ySpeed = 0;
	facingRight = true;
}

Player::Player(std::string filename, float xw, float yw) : Character(),
	sprite(new Sprite(filename)), loadedSprite(true), falling(true) {
	x = xw;
	y = yw;
	xSpeed = 0;
	ySpeed = 0;
	facingRight = true;
}

Player::~Player() {
	if (sprite != NULL) { delete sprite; }

	std::list<Bullet *>::iterator iter;
	for (iter = bullets.begin(); iter != bullets.end(); ++iter) {
		delete *iter;
	}
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

void Player::fire(float dx, float dy) {
	Bullet* b = new Bullet(dx, dy);
	b->setX( (dx > 0) ? (x + sprites[curSprite]->getWidth()) : x );
	// drop the bullet a bit so it looks like its leaving the gun.
	b->setY(y + 10);
	world->addDrawable(b);
	bullets.push_back(b);

	setFire(true, dx);

	Mix_Chunk* shot = SoundManager::getInstance()->load("laser-shot.wav");
	SoundManager::getInstance()->play(shot, 0);
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
//	if (!collidesWithWorld(x, y, getWidth(), getHeight(), xIncr, yIncr)) {
	CollisionType collision = collidesWithWorld(xIncr, yIncr);
	if (collision == NO_COLLISION) {
		x += xIncr;
		y += yIncr;
	}
	else {
		if (!collidesWithWorld(xIncr, 0)) {
			x += xIncr;
		}

//	if (collidesWithWorld(x, y, getWidth(), getHeight(), 0, yIncr)) {
		if (collidesWithWorld(0, yIncr)) {
			if (yIncr > 0) {
				falling = false;
			}
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

  if(curSprite == 0)
    fireDir = 1;
  
  if(fireDir > 0) {
    if(fireInterval < 150)
      curSprite = 14;
    else if(fireInterval < 300)
      curSprite = 15;
    else
      curSprite = 16;
  }
  else {
    if(fireInterval < 150)
      curSprite = 17;
    else if(fireInterval < 300)
      curSprite = 18;
    else
      curSprite = 19; 
  }

  if(fireInterval > 450) {
    justFired = false;
    fireInterval = 0;
    if(fireDir > 0)
      curSprite = 0;
    else
      curSprite = 7;
  }
}


void Player::advanceFrame(Uint32 ticks) {
  interval += ticks;

  // If moving to the right
  if (fabs(interval * xSpeed) > 15000 && xSpeed > 0) {   
	  facingRight = true;
    curSprite = (++curSprite) % (sprites.size()/2);
    if(curSprite > 6 || curSprite == 0)
      curSprite = 1;
    interval = 0;
  }
  // else if moving to the left
  else if (fabs(interval * xSpeed) > 15000 && xSpeed < 0) { 
	  facingRight = false;
    curSprite = (++curSprite) % (sprites.size());
    if(curSprite < 8 || curSprite > 13)
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
