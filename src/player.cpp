#include "player.h"

void Player::update(Uint32 ticks) {
	float incrX = xSpeed * static_cast<float>(ticks) * 0.001;
	float incrY = ySpeed * static_cast<float>(ticks) * 0.001;

	float width = static_cast<float>(frames->at(curFrame).getWidth());
	float height = static_cast<float>(frames->at(curFrame).getHeight());

	xCoordinate += incrX;
	yCoordinate += incrY;

  // World boundary checking for the player
	if(xCoordinate < 0) {
		xCoordinate = 0;
		xSpeed = 0;
	}	
	if(yCoordinate < 0) {
		yCoordinate = 0;
		ySpeed = 0;
	}
	if(xCoordinate > WORLD_WIDTH - width) {
		xCoordinate = WORLD_WIDTH - width;
		xSpeed = 0;
	}
	if(yCoordinate > WORLD_HEIGHT - height) {
		yCoordinate = WORLD_HEIGHT - height;
		ySpeed = 0;
    falling = false;
	}
  if(!justFired)
    advanceFrame(ticks);
  else
    advanceFireFrame(ticks);
}

void Player::advanceFireFrame(Uint32 ticks) {
  fireInterval += ticks;

  if(curFrame == 0)
    fireDir = 1;
  
  if(fireDir > 0) {
    if(fireInterval < 150)
      curFrame = 14;
    else if(fireInterval < 300)
      curFrame = 15;
    else
      curFrame = 16;
  }
  else {
    if(fireInterval < 150)
      curFrame = 17;
    else if(fireInterval < 300)
      curFrame = 18;
    else
      curFrame = 19; 
  }

  if(fireInterval > 450) {
    justFired = false;
    fireInterval = 0;
    if(fireDir > 0)
      curFrame = 0;
    else
      curFrame = 7;
  }
}

void Player::advanceFrame(Uint32 ticks) {
  interval += ticks;
  if (fabs(interval * xSpeed) > 15000 && xSpeed > 0) {   
    curFrame = (++curFrame) % (frames->size()/2);
    if(curFrame > 6 || curFrame == 0)
      curFrame = 1;
    interval = 0;
  }
  else if (fabs(interval * xSpeed) > 15000 && xSpeed < 0) { 
    curFrame = (++curFrame) % (frames->size());
    if(curFrame < 8 || curFrame > 13)
      curFrame = 8;
    interval = 0;
  }
  else if (xSpeed == 0) {
    if(curFrame < 7)
      curFrame = 0;
    else
      curFrame = 7;
  }
}

void Player::incrSpeedX() {
  if(xSpeed < MAX_SPEED && !falling)
    xSpeed += 10;
  else if(xSpeed < MAX_SPEED && (abs(xSpeed) > 20))
    xSpeed += 1;
}

void Player::decrSpeedX() {
  if(xSpeed > -MAX_SPEED && !falling)
    xSpeed -= 10;
  else if(xSpeed > -MAX_SPEED && (abs(xSpeed) > 20))
    xSpeed -= 1;
}

void Player::decelX() {
  if(xSpeed != 0 && (abs(xSpeed) > 10))
    xSpeed *= DECEL;
  else
    xSpeed = 0;
}

void Player::decelY() {
    ySpeed += 10;
}

void Player::jump() {
  if (!falling) {
    ySpeed = -MAX_JUMP;
    falling = true;
  }
}




