/*
 * Camera.h
 *
 *  Created on: Oct 6, 2009
 */

#include <vector>

#include "World.h"
#include "Player.h"
#include "Drawable.h"
#include "TextWriter.h"
#include "Background.h"

#ifndef CAMERA_H_
#define CAMERA_H_

class Camera {
public:
	Camera(World* world, Background* back, unsigned int width, unsigned int height);
	virtual ~Camera();

	unsigned int getWidth() const { return viewWidth; }
	unsigned int getHeight() const { return viewHeight; }

	void setX(int x);
	void setY(int y);

	int getX() const { return cameraX; }
	int getY() const { return cameraY; }

	void snapshot(SDL_Surface* screen, Uint32 ticks);
	void setScrollDelay(unsigned int ticks) { delayScroll = ticks; }

	Player* getFollowedPlayer() const { return tracker; }

private:
	void relocate(unsigned int ticks);
	bool isVisible(SDL_Rect& boundingBox);

	// Blitting methods
	void blitWorld(SDL_Surface* screen);
	void blitTerrain(SDL_Surface* screen);
	void blitDrawables(SDL_Surface* screen, unsigned int ticks);
	void blitWaves(SDL_Surface* screen);
	vector<Drawable*> subjects;
	World* world;
	Background *background;
	Player* tracker;	// the unit that the camera is following

	SDL_Surface* backSurface;

	unsigned int delayScroll;

	int viewWidth;
	int viewHeight;
	float cameraX;
	float cameraY;

	float waveHeight;
};

#endif /* CAMERA_H_ */
