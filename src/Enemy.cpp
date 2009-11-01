/*
 * Enemy.cpp
 *
 *  Created on: Oct 25, 2009
 *      Author: luke
 */

#include "Enemy.h"
#include "Manager.h"

Enemy::Enemy(Sprite* spr) :
	sprite(spr), x(0), y(48), xSpeed(ENEMY_SPEED), ySpeed(0), loadedSprite(false) 
  { interval = 0; }

Enemy::Enemy(std::string filename, float xw, float yw) :
	sprite(new Sprite(filename)), x(xw), y(yw), xSpeed(ENEMY_SPEED), ySpeed(0), 
  loadedSprite(true) { interval = 0; }

Enemy::~Enemy() {
	if (loadedSprite)
		delete sprite;
  //delete sprites;
}

void Enemy::setSprites(vector<Sprite*> *s) {
  sprites = new vector<Sprite*>;
  for(unsigned int i = 0; i < s->size(); ++i) {
    sprites->push_back(s->at(i));
  }
  curSprite = 0;
}

void Enemy::updatePosition(Uint32 ticks) {
	float width = static_cast<float> (sprites->at(curSprite)->getWidth());
	// Cap the player's motion if they are trying to move off of the
	//   left border of the world.
	if (x <= 0 && xSpeed < 0) {
		xSpeed = ENEMY_SPEED;
	}
	// Cap the player's motion if they are trying to move off of the
	//   right border of the world.
	if (x >= Manager::getInstance()->getWorld()->getWidth() - width && xSpeed > 0) {
		xSpeed = -ENEMY_SPEED;
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
    curSprite = (++curSprite) % (sprites->size());
    if(curSprite < 3)
      curSprite = 3;
    interval = 0;
  }
}
