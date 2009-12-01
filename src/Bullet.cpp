/*
 * Bullet.cpp
 *
 *  Created on: Nov 15, 2009
 *  
 */
#include <iostream>
#include "Bullet.h"
#include "Manager.h"
#include "Enemy.h"

Bullet::Bullet(float dx, float dy) {
	xSpeed = dx;
	ySpeed = dy;

	sprites.push_back(new Sprite("laser.bmp"));
	curSprite = 0;

	world = Manager::getInstance()->getWorld();
}

Bullet::~Bullet() {

}

Sprite* Bullet::getSprite() const {
	return sprites[curSprite];
}

void Bullet::updatePosition(Uint32 ticks) {
	float yIncr = ySpeed * static_cast<float> (ticks) * 0.001;
	float xIncr = xSpeed * static_cast<float> (ticks) * 0.001;

	x += xIncr;
	y += yIncr;

	std::list<Enemy *>::const_iterator iter = world->getEnemies().begin();
	//std::list<Enemy *>::const_iterator temp;

	while (iter != world->getEnemies().end()) {
		if ( (x + getWidth() >= (*iter)->getX()) &&
			 (x <= (*iter)->getX() + (*iter)->getWidth()) &&
			 (y + getHeight() >= (*iter)->getY()) &&
			 (y <= (*iter)->getY() + (*iter)->getHeight()) ) {
			   // Make the monster explode.
			   (*iter)->explode();
         iter = world->getEnemies().begin(); 
			   // Get rid of bullet.
			   world->removeDrawable(this);
		} else
		  ++iter;
	}
}
