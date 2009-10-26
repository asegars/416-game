/*
 * Enemy.h
 *
 *  Created on: Oct 25, 2009
 *      Author: luke
 */

#ifndef ENEMY_H_
#define ENEMY_H_

#include "Character.h"
#include "Sprite.h"

class Enemy : public Character {
public:
	Enemy(Sprite* sprite);
	Enemy(std::string filename, float x, float y);
	virtual ~Enemy();

	void draw();
	void update(Uint32 ticks);
	void move(int x, int y);

	int getX() const { return sprite->getX(); }
	int getY() const { return sprite->getY(); }
	float getXSpeed() const { return xSpeed; }
	float getYSpeed() const { return ySpeed; }
	int getWidth() const { return sprite->getWidth(); }
	int getHeight() const { return sprite->getHeight(); }

	virtual void updatePosition(Uint32 ticks);
  virtual Sprite* getSprite() const { return sprite; }

private:
	void adjustViewport();
	Sprite* sprite;
	int xMovement;
	int yMovement;

	float xSpeed;
	float ySpeed;

	static const float playerSpeed = 300;

	bool loadedSprite;
};

#endif /* ENEMY_H_ */
