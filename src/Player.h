/*
 * Player.h
 *
 *  Created on: Oct 5, 2009
 *      Author: luke
 */
#include "Sprite.h"
#include "Character.h"
#include <vector>
using std::vector;

#ifndef PLAYER_H_
#define PLAYER_H_

const int MAX_SPEED = 200;
const int MAX_JUMP = 400;
const int DECEL = 0.95;

class Player : public Character {
public:
	Player(Sprite* sprite);
	Player(std::string filename, float x, float y);
	virtual ~Player();
  void setSprites(vector<Sprite*> *s);

	void draw();
	void update(Uint32 ticks);
  void advanceFrame(Uint32 ticks);

  // Functions specific to user key movements
  void incrSpeedX();
	void decrSpeedX();
	void decelX();
	void decelY();
  void jump();

	float getX() const { return x; }
	float getY() const { return y; }
	void setX(float nx) { x = nx; }
	void setY(float ny) { y = ny; }
	float getXSpeed() const { return xSpeed; }
	float getYSpeed() const { return ySpeed; }
	int getWidth() const { return sprites->at(curSprite)->getWidth(); }
	int getHeight() const { return sprites->at(curSprite)->getHeight(); }
  int getSize() const { return sprites->size(); }

  void setYSpeed(float s) { ySpeed = s; }
  bool isFalling() const { return falling; }

  virtual SDL_Surface* getPlayer() const { return sprite->getSurface(); }
  virtual Sprite* getSprite() const { return sprites->at(curSprite); }
	virtual void updatePosition(Uint32 ticks);

private:
	void adjustViewport();
  vector<Sprite*> *sprites;
  unsigned int curSprite;
  int interval;
	Sprite* sprite;

	float x; 
  float y;
	float xSpeed;
	float ySpeed;

	bool loadedSprite;
  bool falling;
};

#endif /* PLAYER_H_ */
