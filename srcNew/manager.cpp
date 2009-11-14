#include "manager.h"
using std::string;

const unsigned int NUM_ENEMIES = 5;

Manager::~Manager() {
  SDL_FreeSurface(screen);
  SDL_FreeSurface(bgSurface);
  SDL_FreeSurface(bg2Surface);
  SDL_FreeSurface(playerSurface);
  SDL_FreeSurface(enemySurface);
  playerFrames->clear();
  enemyFrames->clear();
  delete playerFrames;
  delete enemyFrames;
}

Manager::Manager() :
  cur_ticks(0), prev_ticks(0), ticks(0),
  screen(SDL_SetVideoMode(VIEW_WIDTH, VIEW_HEIGHT, 16, SDL_HWSURFACE|SDL_DOUBLEBUF)),
  bgSurface(SDL_LoadBMP("images/background.bmp")),
  bg2Surface(SDL_LoadBMP("images/background1.bmp")),
  playerSurface(SDL_LoadBMP("images/hero.bmp")),
  enemySurface(SDL_LoadBMP("images/heckran.bmp")),
  player(50, 1052, 0, 0),
  world(new Frame(bgSurface, screen, WORLD_HEIGHT, WORLD_WIDTH, 0, 0),
        new Frame(bg2Surface, screen, 1200, 900, 0, 0)),
  view(Viewport::getViewport())
  {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
      throw string("Unable to initialize SDL: ");
    }
    if (screen == NULL) { throw string("Unable to set video mode!"); }
    if (bgSurface == NULL) { throw string("No background surface!"); }
    if (bg2Surface == NULL) { throw string("No background2 surface!"); }
    if (playerSurface == NULL) { throw string("No player surface!"); }
    if (enemySurface == NULL) { throw string("No Enemy surface!"); }

    SDL_SetColorKey(bg2Surface, SDL_SRCCOLORKEY|SDL_RLEACCEL, 
      SDL_MapRGB(bg2Surface->format, 0, 0 ,255));
    SDL_SetColorKey(playerSurface, SDL_SRCCOLORKEY|SDL_RLEACCEL, 
      SDL_MapRGB(playerSurface->format, 255, 0 ,0));
    SDL_SetColorKey(enemySurface, SDL_SRCCOLORKEY|SDL_RLEACCEL, 
      SDL_MapRGB(enemySurface->format, 0, 0 ,255));
    srand(time(NULL));
    loadHero();
    loadEnemies();
    view->trackObject(&player);
    atexit(SDL_Quit);
}

void Manager::play() {
  SDL_Event event;
  cur_ticks = SDL_GetTicks();

  bool done = false;
  float hitTimer = 0.0;
  float fireTimer = 1000.0;
  float fireDir = 0.0;
  unsigned int frames = 0;
  float seconds;
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

    fireTimer += ticks;

    seconds = total_ticks * 0.001;
    ++frames;
    if (seconds > 0) 
      fps = frames/seconds;
    else 
      fps = 0;

    cout << "Seconds: " << seconds << endl;
    cout << "FPS : " << fps << endl;

    world.update();
    updateEnemies(ticks);
    player.update(ticks);
    view->update();

    world.draw();
    drawEnemies();
    if(collision()) {
      player.setHit(true);
      hitTimer = 0.0;
    }

    if(player.wasHit() && (hitTimer * .001) < 1.5) {
      if(total_ticks % 100 > 50) 
        player.draw();
      hitTimer += ticks;
    } else {
      player.draw();
      player.setHit(false);
    }

    SDL_Flip(screen);

    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);

    if(event.type == SDL_QUIT)
      done = true;
		if(event.type == SDL_KEYDOWN && keystate[SDLK_ESCAPE]) 
      done = true;
		if(event.type == SDL_KEYDOWN && keystate[SDLK_q])
      done = true;

    if(fireTimer > 450) {
		  if (keystate[SDLK_LEFT])
		    player.decrSpeedX();
		  if (keystate[SDLK_RIGHT])
		    player.incrSpeedX();
		  if (keystate[SDLK_UP] && !player.isFalling())
		    player.jump();
		  if (keystate[SDLK_SPACE] && !player.isFalling() && fireTimer > 1000) {
		    fireDir = player.getXSpeed();
		    player.setXSpeed(0.0);
		    player.setFire(true, fireDir);
        fireTimer = 0.0;      
		  }
		  if (!keystate[SDLK_LEFT] && !keystate[SDLK_RIGHT] && !player.isFalling())
		    player.decelX();
    }
    if (player.isFalling())
      player.decelY();
  }
}

void Manager::loadHero() {
  playerFrames = new vector<Frame>;
  playerFrames->push_back( Frame(playerSurface, screen, 12, 48, 0, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 36, 48, 12, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 35, 48, 48, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 22, 48, 83, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 37, 48, 105, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 33, 48, 142, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 25, 48, 175, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 12, 48, 388, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 36, 48, 352, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 35, 48, 317, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 22, 48, 295, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 37, 48, 258, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 33, 48, 225, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 25, 48, 200, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 43, 48, 400, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 43, 48, 443, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 44, 48, 486, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 43, 48, 617, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 43, 48, 574, 0));
  playerFrames->push_back( Frame(playerSurface, screen, 44, 48, 530, 0));
  player.setFrames(playerFrames);
}

void Manager::loadEnemies() {
  enemyFrames = new vector<Frame>;
  enemyFrames->push_back( Frame(enemySurface, screen, 43, 48, 0, 0));
  enemyFrames->push_back( Frame(enemySurface, screen, 43, 48, 43, 0));
  enemyFrames->push_back( Frame(enemySurface, screen, 43, 48, 86, 0));
  enemyFrames->push_back( Frame(enemySurface, screen, 43, 48, 129, 0));
  enemyFrames->push_back( Frame(enemySurface, screen, 43, 48, 172, 0));
  enemyFrames->push_back( Frame(enemySurface, screen, 43, 48, 215, 0));
  for(unsigned int i = 0; i < NUM_ENEMIES; ++i) {
    enemies.push_back( Enemy((rand() % WORLD_WIDTH), 1152, ENEMY_SPEED, 0));
    enemies.at(i).setFrames(enemyFrames);
  }
}

void Manager::drawEnemies() {
  for(unsigned int i = 0; i < enemies.size(); ++i)
    enemies.at(i).draw();
}

void Manager::updateEnemies(Uint32 ticks) {
  for(unsigned int i = 0; i < enemies.size(); ++i)
    enemies.at(i).update(ticks);
}

bool Manager::collision() {

  float width, height;
  float playerWidth = player.getWidth();
  float playerHeight = player.getHeight();
  
  for(unsigned int i = 0; i < enemies.size(); ++i) {
    width = enemies.at(i).getWidth();
    height = enemies.at(i).getHeight();
    
    if(enemies.at(i).getX() + width - 5 < player.getX())
      continue;
    if(enemies.at(i).getX() > player.getX() + playerWidth - 5)
      continue;
    if(enemies.at(i).getY() + height - 5 < player.getY())
      continue;
    if(enemies.at(i).getY() > player.getY() + playerHeight - 5)
      continue;
    return true;
  }
  
  return false;
}
