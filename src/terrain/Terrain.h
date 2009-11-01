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
	Terrain(Sprite* terrainSprite, int x, int y);
	virtual ~Terrain();

	int getWidth() { return width; }
	int getHeight() { return height; }
    virtual float getX() const { return xLoc; }
    virtual float getY() const { return yLoc; }
	virtual Sprite* getSprite() const { return sprite; }
	virtual void updatePosition(Uint32 ticks) {}

	static int getSize() { return width; }
protected:
	Sprite* sprite;
	int xLoc, yLoc;
	static int width, height;
};

#endif /* TERRAIN_H_ */
