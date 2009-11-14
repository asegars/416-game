#include <string>
#include <vector>
using std::vector;
#include "Sprite.h"
#include "Drawable.h"

#ifndef BACKGROUND_H_
#define BACKGROUND_H_

class Background : public Drawable {
public:
  Background();
  virtual ~Background();

  float getX() const { return 0; }
  float getY() const { return 0; }
	int getWidth() const { return bgs.at(0)->getWidth(); }
	int getHeight() const { return bgs.at(0)->getHeight(); }
	Sprite* getSprite() const { return bgs.at(0); }

	int getWidth(int i) const { return bgs.at(i)->getWidth(); }
	int getHeight(int i) const { return bgs.at(i)->getHeight(); }
	Sprite* getSprite(int i) const { return bgs.at(i); }

	virtual void updatePosition(Uint32) { }

private:
  vector<Sprite*> bgs;
};

#endif
