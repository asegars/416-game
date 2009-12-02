/*
 * Target.cpp
 *
 *  Created on: Dec 2, 2009
 *  
 */

#include "Target.h"
#include "Sprite.h"

Target::Target() {
	sprite = new Sprite("escape-boat.bmp");
	// The boat doesn't move.
	xSpeed = 0;
	ySpeed = 0;

	// The position will be changed when the map is read in, but start it
	//   off out of sight.
	x = 0;
	y = 0;


}

Target::~Target() {

}

Sprite* Target::getSprite() const {
	return sprite;
}

void Target::updatePosition(Uint32 ticks) {

}
