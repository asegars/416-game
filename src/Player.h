/*
 * Player.h
 *
 *  Created on: Oct 5, 2009
 *      Author: luke
 */
#include "Sprite.h"
#include "Drawable.h"

#ifndef PLAYER_H_
#define PLAYER_H_

class Player : public Drawable {
public:
	Player(Sprite* sprite);
	Player(std::string filename, float x, float y);
	virtual ~Player();

	void draw();
	void update(Uint32 ticks);
	void move(int x, int y);

	int getX() const { return sprite->getX(); }
	int getY() const { return sprite->getY(); }
	float getXSpeed() const { return xSpeed; }
	float getYSpeed() const { return ySpeed; }
	int getWidth() const { return sprite->getWidth(); }
	int getHeight() const { return sprite->getHeight(); }

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
};

#endif /* PLAYER_H_ */
