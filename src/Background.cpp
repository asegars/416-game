#include "Background.h"

Background::Background() {
  bgs.push_back(new Sprite("waterfall.bmp"));
}

Background::~Background() {
  for(unsigned int i = 0; i < bgs.size(); ++i) {
    if (bgs.at(i) != NULL) delete bgs.at(i);
  }
}
