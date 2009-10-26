/*
 * FontLibrary.cpp
 *
 *  Created on: Oct 25, 2009
 *      Author: luke
 */

#include <string>
#include <iostream>
#include "FontLibrary.h"

// Reserve space for the FontLibrary instance.
FontLibrary* FontLibrary::instance = NULL;

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
	for (unsigned int i = 0; i < fonts.size(); ++i) {
		if (fonts[i] != NULL) {
			TTF_CloseFont(fonts[i]);
		}
	}
}

FontLibrary* FontLibrary::getInstance() {
	if (instance == NULL) {
		instance = new FontLibrary();
	}
	return instance;
}

void FontLibrary::loadFonts() {
	fonts.push_back(TTF_OpenFont("fonts/FreeSansBold.ttf", 16));
}

/**
 * Returns the specified font in the given pixel size.
 *
 * Note: the pixel size is currently ignored.
 */
TTF_Font* FontLibrary::getFont(Font font, int size) const {
	// TODO: Dynamically load fonts if they are requested and not stored.
	if (font >= 0 && font < fonts.size()) {
		return fonts[font];
	}
	else {
		throw std::string("Invalid font requested!");
	}
}

