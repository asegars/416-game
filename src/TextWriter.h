/*
 * TextWriter.h
 *
 *  Created on: Oct 25, 2009
 */

#ifndef TEXTWRITER_H_
#define TEXTWRITER_H_

#include "FontLibrary.h"

class TextWriter {
public:
	TextWriter();
	virtual ~TextWriter();

	void switchFont(Font newFont) { font = newFont; }
	void switchSize(int newSize) { size = newSize; }
	void switchColor(int r, int g, int b) { color.r = r; color.g = g; color.b = b; }
	void write(const char* message, SDL_Surface* surface, int x, int y);

private:
	FontLibrary* fontLib;
	TTF_Font* activeFont;
	Font font;
	int size;
	SDL_Color color;
};

#endif /* TEXTWRITER_H_ */
