/*
 * Sprite.h
 *
 *  Created on: Oct 6, 2009
 */
#include <SDL/SDL.h>
#include <iostream>
#include <string>

#ifndef SPRITE_H_
#define SPRITE_H_

class Sprite {
public:
	Sprite(std::string filename);
  Sprite(float x, float y, int w, int h, SDL_Surface* i) : posX(x), 
     posY(y), width(w), height(h), image(i) { }
	virtual ~Sprite();

	unsigned int getWidth() const { return width; }
	unsigned int getHeight() const { return height; }
  float getPosX() const { return posX; }
  float getPosY() const { return posY; }
	SDL_Surface* getSurface() const { return image; }
private:
  float posX; 
  float posY;
	unsigned int width;
	unsigned int height;
	SDL_Surface* image;
	bool loadedImage;
};

#endif /* SPRITE_H_ */
