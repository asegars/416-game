/*
 * Bullet.h
 *
 *  Created on: Nov 15, 2009
 *  
 */

#ifndef BULLET_H_
#define BULLET_H_

#include "Character.h"

class Bullet : public Character {
public:
	Bullet(float dx, float dy);
	virtual ~Bullet();


	virtual Sprite* getSprite() const;
	virtual void updatePosition(Uint32 ticks);
};

#endif /* BULLET_H_ */
