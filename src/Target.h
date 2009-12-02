/*
 * Target.h
 *
 *  Created on: Dec 2, 2009
 *  
 */

#ifndef TARGET_H_
#define TARGET_H_

#include <iostream>
#include "Character.h"
#include "Sprite.h"

class Target : public Character {
public:
	Target();
	virtual ~Target();

	virtual float getX() const { return x; }
	virtual float getY() const { return y; }
	virtual int getWidth() const { return sprite->getWidth(); }
	virtual int getHeight() const { return sprite->getHeight(); }

	void setX(float nx) { x = nx; }
	void setY(float ny) { y = ny; }
	void setLocation(float nx, float ny) { std::cout << "Updating boat location." << std::endl; setX(nx); setY(ny); }

	virtual Sprite* getSprite() const;
	virtual void updatePosition(Uint32 ticks);

private:
	Sprite* sprite;
	float x, y;
};

#endif /* TARGET_H_ */
