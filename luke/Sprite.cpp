/*
 * Sprite.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */

#include <SDL/SDL_image.h>
#include "Sprite.h"

Sprite::Sprite(std::string filename, float x, float y) {
	image = IMG_Load(filename.c_str());

	this->x = x;
	this->y = y;

	width = image->w;
	height = image->h;

	// For future use.  This is currently always true.
	loadedImage = true;
}

Sprite::~Sprite() {
	if (loadedImage) {
		SDL_FreeSurface(image);
	}
}
