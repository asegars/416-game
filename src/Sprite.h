/*
 * Sprite.h
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */
#include <SDL/SDL.h>
#include <string>

#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite {
public:
	Sprite(std::string filename, float x, float y);
  Sprite(float posX, float posY, int w, int h, SDL_Surface* i) : x(posX), 
     y(posY), width(w), height(h), image(i) {}
	virtual ~Sprite();

	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }
	float getX() const { return x; }
	float getY() const { return y; }
	void setX(float nx) { x = nx; }
	void setY(float ny) { y = ny; }
	SDL_Surface* getSurface() const { return image; }
private:
	float x;
	float y;
	unsigned int width;
	unsigned int height;
	SDL_Surface* image;
	bool loadedImage;
};

#endif /* SPRITE_H_ */
