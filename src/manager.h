#include <SDL.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; 

#include "sprite.h"
#include "world.h"
#include "player.h"
#include "enemy.h"
#include "viewport.h"

class Manager {
public:
  Manager ();
  ~Manager ();

  void play();
  void loadHero();
  void loadEnemies();
  void drawEnemies();
  void updateEnemies(Uint32);
  bool collision();

private:
  Uint32 cur_ticks;
  Uint32 prev_ticks;
  Uint32 ticks;

  SDL_Surface *screen;
  SDL_Surface *bgSurface;
  SDL_Surface *playerSurface;
  SDL_Surface *enemySurface;

  vector<Frame> *playerFrames;
  vector<Frame> *enemyFrames;
  vector<Enemy> enemies;
  Player player;
  World world;
  Viewport *view;
};
