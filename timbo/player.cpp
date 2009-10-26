#include "player.h"

void Player::update(Uint32 ticks) {
	float incrX = xSpeed * static_cast<float>(ticks) * 0.001;
	float incrY = ySpeed * static_cast<float>(ticks) * 0.001;

	float width = static_cast<float>(frame->getWidth());		  //Player width
	float height = static_cast<float>(frame->getHeight());		//Player height

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
	if(yCoordinate > (WORLD_HEIGHT - height)) {
		yCoordinate = WORLD_HEIGHT - height;
		ySpeed = 0;
	}

  // Viewport boundary checking
  if (xSpeed > 0) {
    if (xCoordinate <= VIEW_WIDTH - CUSHIONX - width) {
      playerX = xCoordinate;
    }
    if (xCoordinate >= WORLD_WIDTH - CUSHIONX - width) {
      playerX = xCoordinate - WORLD_WIDTH + VIEW_WIDTH ;
    }

    if ( (xCoordinate > VIEW_WIDTH - CUSHIONX - width) &&
            (xCoordinate < WORLD_WIDTH - CUSHIONX - width) ) {
      float viewX = xCoordinate-(VIEW_WIDTH - CUSHIONX - width);
      view->setX(viewX);
    }
  } else {
    if (xCoordinate >= VIEW_WIDTH + CUSHIONX) {
      playerX = xCoordinate - VIEW_WIDTH;
    }
    if (xCoordinate <= CUSHIONX) {
      playerX = xCoordinate;
    }

    if ( (xCoordinate < VIEW_WIDTH + CUSHIONX) &&
            (xCoordinate > CUSHIONX) ) {
      float viewX = xCoordinate - CUSHIONX;
      view->setX(viewX);
    }
  }

  if(ySpeed > 0) {
    if (yCoordinate <= VIEW_HEIGHT - CUSHIONY - height) {
      playerY = yCoordinate;
    }
    if (yCoordinate >= WORLD_HEIGHT - CUSHIONY - height) {
      playerY = yCoordinate - WORLD_HEIGHT + VIEW_HEIGHT;
    }

    if ( (yCoordinate > VIEW_HEIGHT - CUSHIONY - height) &&
              (yCoordinate <  WORLD_HEIGHT - CUSHIONY - height) ) {
      float viewY = yCoordinate-(VIEW_HEIGHT - CUSHIONY - height);
      view->setY(viewY);
    }
  } else {
    if (yCoordinate >= VIEW_HEIGHT + CUSHIONY) {
      playerY = yCoordinate - VIEW_HEIGHT;
    }
    if (yCoordinate <= CUSHIONY) {
      playerY = yCoordinate;
    }

    if ( (yCoordinate < VIEW_HEIGHT + CUSHIONY) &&
              (yCoordinate > CUSHIONY) ) {
      float viewY = yCoordinate-CUSHIONY;
      view->setY(viewY);
    }
  }
}

void Player::incrSpeedX() {
  if(xSpeed < MAX_SPEED)
    xSpeed += 10;
}

void Player::decrSpeedX() {
  if(xSpeed > -MAX_SPEED)
    xSpeed -= 10;
}

void Player::incrSpeedY() {
  if(ySpeed < MAX_SPEED)
    ySpeed += 10;
}

void Player::decrSpeedY() {
  if(ySpeed > -MAX_SPEED)
    ySpeed -= 10;
}

void Player::decelX() {
  if(xSpeed != 0 && (abs(xSpeed) > 10))
    xSpeed *= DECEL;
  else
    xSpeed = 0;
}

void Player::decelY() {
  if(ySpeed != 0 && (abs(ySpeed) > 10))
    ySpeed *= DECEL;
  else
    ySpeed = 0;
}




