/*
 * Enemy.h
 *
 *  Created on: Oct 25, 2009
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include <vector>
#include "Character.h"
#include "Player.h"
#include "Sprite.h"
using std::vector;

const int ENEMY_SPEED = 50;

class Enemy : public Character {
public:
	Enemy(Sprite* sprite);
	Enemy(std::string filename, float xw, float yw, float xs);
	virtual ~Enemy();
  void setSprites(vector<Sprite*> &s);

  void advanceFrame(Uint32 ticks);
  void playerToAttack(Player *p) { player = p; }

	float getX() const { return x; }
	float getY() const { return y; }
	void setX(float nx) { x = nx; }
	void setY(float ny) { y = ny; }
	float getXSpeed() const { return xSpeed; }
	float getYSpeed() const { return ySpeed; }
	int getWidth() const { return sprites.at(curSprite)->getWidth(); }
	int getHeight() const { return sprites.at(curSprite)->getHeight(); }
  int getSize() const { return sprites.size(); }

  virtual SDL_Surface* getEnemy() const { return sprite->getSurface(); }
  virtual Sprite* getSprite() const { return sprites.at(curSprite); }
	virtual void updatePosition(Uint32 ticks);

private:
	void adjustViewport();
//  vector<Sprite*> sprites;
//  unsigned int curSprite;
  int interval;
	Sprite* sprite;
  Player* player; 

//	float x;
//  float y;
//	float xSpeed;
//	float ySpeed;

	bool loadedSprite;
};

#endif /* ENEMY_H_ */
