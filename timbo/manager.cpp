#include <cmath>
#include <cstdlib>
#include "manager.h"
using std::string;

const int MAX_BALLS = 10;

Manager::~Manager() {
  delete playerFrame;
  delete playerFrame2;
  delete fireFrame;
  delete boomFrame;
  SDL_FreeSurface(screen);
  SDL_FreeSurface(bgSurface);
  SDL_FreeSurface(playerSurface);
  SDL_FreeSurface(playerSurface2);
  SDL_FreeSurface(fireSurface);
  SDL_FreeSurface(boomSurface);
}

Manager::Manager() :
  cur_ticks(0), prev_ticks(0), ticks(0),
  screen(SDL_SetVideoMode(VIEW_WIDTH, VIEW_HEIGHT, 16, SDL_HWSURFACE)),
  bgSurface(SDL_LoadBMP("images/snownight.bmp")),
  playerSurface(SDL_LoadBMP("images/snowman1.bmp")),
  playerSurface2(SDL_LoadBMP("images/snowman2.bmp")),
  fireSurface(SDL_LoadBMP("images/fireball.bmp")),
  boomSurface(SDL_LoadBMP("images/boom.bmp")),
  playerFrame(new Frame(playerSurface, screen, 70, 89, 0, 0)),
  playerFrame2(new Frame(playerSurface2, screen, 70, 89, 0, 0)),
  fireFrame(new Frame(fireSurface, screen, 56, 59, 0, 0)),
  boomFrame(new Frame(boomSurface, screen, 70, 89, 0, 0)),
  player(0, 0, 0, 0, playerFrame),
  world(new Frame(bgSurface, screen, WORLD_WIDTH, WORLD_HEIGHT, 0, 0))
  {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw string("Unable to initialize SDL: ");
    }
    if (screen == NULL) { throw string("Unable to set video mode!"); }
    if (bgSurface == NULL) { throw string("No background surface!"); }
    if (playerSurface == NULL) { throw string("No player surface!"); }
    if (fireSurface == NULL) { throw string("No fireball surface!"); }
    Uint32 colorkey = SDL_MapRGB(playerSurface->format, 255, 0, 255);
    SDL_SetColorKey(playerSurface, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
    //colorkey = SDL_MapRGB(playerSurface2->format, 255, 0, 255);
    SDL_SetColorKey(playerSurface2, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
    //colorkey = SDL_MapRGB(fireSurface->format, 255, 0, 255);
    SDL_SetColorKey(fireSurface, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
    //colorkey = SDL_MapRGB(boomSurface->format, 255, 0, 255);
    SDL_SetColorKey(boomSurface, SDL_SRCCOLORKEY|SDL_RLEACCEL, colorkey);
    srand(time(NULL));
    makeFire();
    atexit(SDL_Quit);
}

void Manager::play() {
  SDL_Event event;
  cur_ticks = SDL_GetTicks();

  bool done = false;
  bool pause = false;
  unsigned int frames = 0;
  float seconds = 0;
  float fps;
  unsigned int total_ticks = 0;
  unsigned int tick_sum = 0;
  SDL_EnableKeyRepeat(250, 50);
  SDL_EnableUNICODE(1);
  while ( ! done ) {
    prev_ticks = cur_ticks;
    cur_ticks = SDL_GetTicks();
    ticks = cur_ticks-prev_ticks;
    tick_sum += ticks;
    total_ticks += ticks;

    seconds = total_ticks * 0.001;
    ++frames;
    if (seconds > 0) 
      fps = frames/seconds;
    else 
      fps = 0;

    cout << "Seconds: " << seconds << endl;
    cout << "FPS : " << fps << endl;

    if (!pause) {
      world.draw();
      world.update();

      drawFire();
      updateFire(ticks);

      if(!collision()) {
        if(player.getXSpeed() >= 0)
          player.replaceFrame(playerFrame);
        else if(player.getXSpeed() < 0)
          player.replaceFrame(playerFrame2);
      } 
      else
        player.replaceFrame(boomFrame);
    }

    player.draw();
    player.update(ticks);

    SDL_Flip(screen);


    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if(event.type == SDL_QUIT)
      done = true;
		if(event.type == SDL_KEYDOWN && keystate[SDLK_ESCAPE]) 
      done = true;
		if(event.type == SDL_KEYDOWN && keystate[SDLK_q])
      done = true;

    if (keystate[SDLK_LEFT])
      player.decrSpeedX();
    if (keystate[SDLK_RIGHT])
      player.incrSpeedX();
    if (keystate[SDLK_UP])
      player.decrSpeedY();
    if (keystate[SDLK_DOWN])
      player.incrSpeedY();
    // if (keystate[SDLK_SPACE])
    //   player.setYSpeed(-300);
    if (!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT])
      player.decelX();
    if (!keystate[SDLK_UP] && !keystate[SDLK_DOWN])
      player.decelY();
  }
}

void Manager::makeFire() {
  int i = 0;
  float x, y, xs, ys;
  for(i = 0; i < MAX_BALLS; ++i) {
    x = rand() % WORLD_WIDTH;
    y = rand() % WORLD_HEIGHT;
    xs = (rand() % 300) + 200;
    ys = (rand() % 300) + 200;
    balls.push_back(Fireball(x, y, xs, ys, fireFrame));
  }
}

void Manager::drawFire() {
  for(unsigned int i = 0; i < balls.size(); ++i)
    balls.at(i).draw();
}

void Manager::updateFire(Uint32 ticks) {
  for(unsigned int i = 0; i < balls.size(); ++i)
    balls.at(i).update(ticks);
}

bool Manager::collision() {

  float width = fireFrame->getWidth();
  float height = fireFrame->getHeight();
  float playerWidth = playerFrame->getWidth();
  float playerHeight = playerFrame->getHeight();
  
  for(unsigned int i = 0; i < balls.size(); ++i) {
    Fireball &current = balls.at(i);
    if(current.getX() + width - 5 < player.getX()) {
      continue;
    }
    if(current.getX() > player.getX() + playerWidth - 5) {
      continue;
    }
    if(current.getY() + height - 5< player.getY()) {
      continue;
    }
    if(current.getY() > player.getY() + playerHeight - 5) {
      continue;
    }
    return true;
  }
  
  return false;
}
