/*
 * Enemy.cpp
 *
 *  Created on: Oct 25, 2009
 */

#include <cmath>
#include "Enemy.h"
#include "Manager.h"

Enemy::Enemy(Sprite* spr) :	sprite(spr) {
	x = 0;
	y = 48;
	xSpeed = rand() % ENEMY_SPEED + 50;
	ySpeed = 0;
	loadedSprite = false;
	interval = 0;
}

Enemy::Enemy(std::string filename, float xw, float yw, float xs) : 
    sprite(new Sprite(filename)) {
	x = xw;
	y = yw;
	xSpeed = xs;
	ySpeed = 0;
	loadedSprite = true;
	interval = 0;
}

Enemy::~Enemy() {
	if (sprite != NULL) { delete sprite; }
//	if (sprites != NULL) { delete sprites; }
}

void Enemy::setSprites(vector<Sprite*> &s) {
//  sprites = new vector<Sprite*>;
  for(unsigned int i = 0; i < s.size(); ++i) {
    sprites.push_back(s.at(i));
  }
  curSprite = 0;
}

void Enemy::updatePosition(Uint32 ticks) {
	// float width = static_cast<float> (sprites.at(curSprite)->getWidth());
	// Cap the player's motion if they are trying to move off of the
	//   left border of the world.
	if (x <= player->getX()) {
		xSpeed = abs(xSpeed);
	}
	// Cap the player's motion if they are trying to move off of the
	//   right border of the world.
	if (x >= player->getX()) {
		xSpeed = -fabs(xSpeed);
	}
	float incr = xSpeed * static_cast<float> (ticks) * 0.001;
	x += incr;
  advanceFrame(ticks);
}

void Enemy::advanceFrame(Uint32 ticks) {
  interval += ticks;
  if (fabs(interval * xSpeed) > 15000 && xSpeed > 0) {
    curSprite = (++curSprite);
    if(curSprite > 2)
      curSprite = 0;
    interval = 0;
  }
  else if (fabs(interval * xSpeed) > 15000 && xSpeed < 0) {
    curSprite = (++curSprite) % (sprites.size());
    if(curSprite < 3)
      curSprite = 3;
    interval = 0;
  }
}
