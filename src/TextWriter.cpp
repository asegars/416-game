/*
 * TextWriter.cpp
 *
 *  Created on: Oct 25, 2009
 *      Author: luke
 */

#include <iostream>
#include "TextWriter.h"
#include "Manager.h"
#include "FontLibrary.h"

TextWriter::TextWriter() {
	color.r = 0;
	color.g = 0;
	color.b = 0;

	size = 14;
	font = FREE_SANS;

	fontLib = Manager::getInstance()->getFontLibrary();
	activeFont = fontLib->getFont(font, size);
}

TextWriter::~TextWriter() {

}

void TextWriter::write(const char* message, SDL_Surface* surface, int x, int y) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(activeFont, message, color);

	SDL_Rect location = {x, y, 0, 0};
	SDL_BlitSurface(textSurface, NULL, surface, &location);
	SDL_FreeSurface(textSurface);
}
