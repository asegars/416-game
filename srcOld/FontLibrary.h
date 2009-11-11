/*
 * FontLibrary.h
 *
 *  The FontLibrary is a singleton that contains an active reference
 *  to all of the fonts required by the game.  Fonts can be loaded
 *  a single time and then requested from the FontLibrary's cache
 *  to prevent multiple loads.
 *
 *  FontLibrary.getFont() can be used to request a particular font.
 *  If the font has not yet been loaded, it will be loaded on
 *  request and automatically stored in the cache.
 *
 *  NOTE: The font SIZE is currently ignored.  This will not be
 *  the case for long.
 */

#ifndef FONTLIBRARY_H_
#define FONTLIBRARY_H_

#include <SDL/SDL_ttf.h>
#include <vector>
using std::vector;

enum Font { FREE_SANS = 0, AGENT = 1 };

// TODO: Convert this to the ResourceManager family tree.
class FontLibrary {
public:
	static FontLibrary* getInstance();
	virtual ~FontLibrary();

	TTF_Font* getFont(Font, int) const;

private:
	std::vector<TTF_Font *> fonts;
	static FontLibrary* instance;

	FontLibrary();
	void loadFonts();
};

#endif /* FONTLIBRARY_H_ */
