/*
 * Player.h
 *
 *  Created on: Oct 5, 2009
 *      Author: luke
 */
#include "Sprite.h"
#include "Character.h"

#ifndef PLAYER_H_
#define PLAYER_H_

const int MAX_SPEED = 300;
const int DECEL = 0.97;

class Player : public Character {
public:
	Player(Sprite* sprite);
	Player(std::string filename, float x, float y);
	virtual ~Player();

	void draw();
	void update(Uint32 ticks);
	void move(int x, int y);

  // Functions specific to user key movements
  void incrSpeedX();
	void decrSpeedX();
	void incrSpeedY();
	void decrSpeedY();
	void decelX();
	void decelY();
  void jump();

	int getX() const { return sprite->getX(); }
	int getY() const { return sprite->getY(); }
	float getXSpeed() const { return xSpeed; }
	float getYSpeed() const { return ySpeed; }
	int getWidth() const { return sprite->getWidth(); }
	int getHeight() const { return sprite->getHeight(); }

  void setYSpeed(float s) { ySpeed = s; }
  bool isFalling() const { return falling; }

	virtual Sprite* getSprite() const { return sprite; }
	virtual void updatePosition(Uint32 ticks);

private:
	void adjustViewport();
	Sprite* sprite;
	int xMovement;
	int yMovement;

	float xSpeed;
	float ySpeed;

	static const float playerSpeed = 300;

	bool loadedSprite;
  bool falling;
};

#endif /* PLAYER_H_ */
