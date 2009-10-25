#include <SDL.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; 

#include "viewport.h"
#include "sprite.h"
#include "world.h"
#include "player.h"
#include "fireball.h"

class Manager {
public:
  Manager ();
  ~Manager ();

  void play();
  void makeFire();
  void drawFire();
  void updateFire(Uint32);
  bool collision();

private:
  Uint32 cur_ticks;
  Uint32 prev_ticks;
  Uint32 ticks;

  SDL_Surface *screen;
  SDL_Surface *bgSurface;
  SDL_Surface *playerSurface;
  SDL_Surface *playerSurface2;
  SDL_Surface *fireSurface;
  SDL_Surface *boomSurface;

  Frame *playerFrame;
  Frame *playerFrame2;
  Frame *fireFrame;
  Frame *boomFrame;
  Player player;
  World world;

  vector<Fireball> balls;
};
