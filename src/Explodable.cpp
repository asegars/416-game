/*
 * Explodable.cpp
 *
 *  Created on: Nov 16, 2009
 *  
 */

#include "Explodable.h"
#include "World.h"

const int EXPLOSION_SPEED = 200;

Explodable::Explodable(int xLoc, int yLoc, Sprite* s, World* w) : world(w){
  setX(xLoc);
  setY(yLoc);
  sprites.push_back(s);
  curSprite = 0;
  makeChunks(CHUNKS);
}

Explodable::~Explodable() {
	//chunks.clear();
}

void Explodable::updatePosition(Uint32 ticks) { 
  /*std::vector<ExplodingCharacter>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->updatePosition(ticks);
    if (ptr->goneTooFar()) {
      world->removeDrawable(&(*ptr));
      ptr = chunks.erase(ptr);
    }   
    else ++ptr;
  }*/
}

void Explodable::makeChunks(unsigned int n) { 
  unsigned int chunk_width = sprites.at(0)->getWidth()/n;
  unsigned int chunk_height = sprites.at(0)->getHeight()/n;
  Sint16 source_x = sprites.at(0)->getPosX();
  Sint16 source_y = sprites.at(0)->getPosY();
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < n; ++j) {
      float speed_x = (rand() % EXPLOSION_SPEED + 40) * (rand()%2?-1:1); 
      float speed_y = (rand() % EXPLOSION_SPEED + 40) * (rand()%2?-1:1); 
      world->addDrawable(new ExplodingCharacter(
                getX()+i*chunk_width,  // x coord of destination 
                getY()+j*chunk_height, // y coord of destination
                speed_x, speed_y, new Sprite(
                source_x+i*chunk_width, 
                source_y+j*chunk_height,
                chunk_width, chunk_height, sprites.at(0)->getSurface()),
                world));
      // chunks.push_back(c);
      // world->addDrawable(&c);
    }
  }
}
