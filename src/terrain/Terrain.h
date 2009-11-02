/*
 * Terrain.h
 *
 *  Created on: Oct 28, 2009
 *      Author: alsegars
 */

#ifndef TERRAIN_H_
#define TERRAIN_H_

#include "../Sprite.h"
#include "../Drawable.h"

class Terrain : public Drawable {
public:
	Terrain(Sprite* terrainSprite);
	virtual ~Terrain();

//	int getX() { return xLoc; }
//	int getY() { return yLoc; }
	int getWidth() { return width; }
	int getHeight() { return height; }
    virtual float getX() const { return 0; }
    virtual float getY() const { return 0; }
	virtual Sprite* getSprite() const { return sprite; }
	virtual void updatePosition(Uint32) {}

	static int getSize() { return width; }
protected:
	Sprite* sprite;
	static int width, height;
};

#endif /* TERRAIN_H_ */
