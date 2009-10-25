/*
 * Drawable.h
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include "Sprite.h"

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

class Drawable {
public:
	Drawable();
	virtual ~Drawable();

	virtual Sprite* getSprite() const = 0;
	virtual void updatePosition(Uint32 ticks) = 0;
};

#endif /* DRAWABLE_H_ */
