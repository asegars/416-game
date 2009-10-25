#ifndef FRAME__H
#define FRAME__H

#include <iostream>
#include <SDL.h>

class Frame {
public:
  // Must pass both width and height here because the sprite might
  // not consist of the whole surface, only part of the surface.
  Frame( SDL_Surface* spr, SDL_Surface* scr,
      Uint16 sprite_width, Uint16 sprite_height,
      Sint16 src_x, Sint16 src_y);

  void draw(Sint16 x, Sint16 y);
  void draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy);

  Uint16 getWidth()  const { return spriteWidth; }
  Uint16 getHeight() const { return spriteHeight; }

private:
  SDL_Surface * sprite;
  SDL_Surface * screen;
  Uint16 spriteWidth;
  Uint16 spriteHeight;
  Sint16 spriteSourceX;
  Sint16 spriteSourceY;
};

#endif
