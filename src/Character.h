/*
 * Character.h
 *
 *  Created on: Oct 25, 2009
 *      Author: luke
 */

#ifndef CHARACTER_H_
#define CHARACTER_H_

#include "Drawable.h"

class Character : public Drawable {
public:
	Character();
	virtual ~Character();

  virtual float getX() const { return 0; }
  virtual float getY() const { return 0; }
};

#endif /* CHARACTER_H_ */
