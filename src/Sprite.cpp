/*
 * Sprite.cpp
 *
 *  Created on: Oct 6, 2009
 *      Author: luke
 */

#include <iostream>
#include <SDL/SDL_image.h>
#include "Sprite.h"

Sprite::Sprite(std::string filename) {
	image = IMG_Load(filename.c_str());
  posX = 0;
  posY = 0;

	width = image->w;
	height = image->h;

	// For future use.  This is currently always true.
	loadedImage = true;
	std::cout << "Loaded sprite [" << filename << "]" << std::endl;
}

Sprite::~Sprite() {
	if (loadedImage) {
		SDL_FreeSurface(image);
	}
}
