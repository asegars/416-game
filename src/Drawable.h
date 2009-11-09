/*
 * Drawable.h
 *
 *  Created on: Oct 6, 2009
 */
#include "Sprite.h"

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

class Drawable {
public:
	Drawable();
	virtual ~Drawable();

	virtual Sprite* getSprite() const = 0;
  virtual float getX() const = 0;
  virtual float getY() const = 0;
	virtual void updatePosition(Uint32 ticks) = 0;
};

#endif /* DRAWABLE_H_ */
