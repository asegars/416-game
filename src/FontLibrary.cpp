/*
 * FontLibrary.cpp
 *
 *  Created on: Oct 25, 2009
 */

#include <string>
#include <iostream>
#include <map>
#include <SDL/SDL_ttf.h>
#include "FontLibrary.h"

// Reserve space for the FontLibrary instance.
FontLibrary* FontLibrary::instance = NULL;

// TODO: Convert to new manager framework to standardize interface & improve memory management.
FontLibrary::FontLibrary() {
	if (TTF_Init() == -1) {
		throw std::string("TTF error: ") + TTF_GetError();
	}

	loadFonts();
}

/**
 * Free all of the fonts in the library when the class is killed.
 */
FontLibrary::~FontLibrary() {
	std::map<std::pair<Font, unsigned int>, TTF_Font*>::iterator iter = fonts.begin();

	while (iter != fonts.end()) {
		TTF_CloseFont(iter->second);
		iter++;
	}
	fonts.clear();
}

FontLibrary* FontLibrary::getInstance() {
	if (instance == NULL) {
		instance = new FontLibrary();
	}
	return instance;
}

void FontLibrary::loadFonts() {
}

unsigned int FontLibrary::toKey(Font font, unsigned int size) {
	return (font * 1000) + size;
}

/*
 * Returns the specified font in the given pixel size.
 *
 * Note: the pixel size is currently ignored.
 */
TTF_Font* FontLibrary::getFont(Font font, unsigned int size) {
	std::pair<Font, unsigned int> key;
	key.first = font;
	key.second = size;

	if (fonts.find(key) != fonts.end()) {
		return fonts[key];
	}
	else {
		// Attempt to load the font.
		if (font == FREE_SANS) {
			fonts[key] = TTF_OpenFont("fonts/FreeSansBold.ttf", size);
      return fonts[key];
		}
		else /*if (font == AGENT)*/ {
			fonts[key] = TTF_OpenFont("fonts/AgentOrange.ttf", size);
      return fonts[key];
		}
	}
}

