#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H
#include <iostream>
#include "multisprite.h"
#include "ioManager.h"

class SmartSprite : public Sprite {
public:
  SmartSprite(const std::string&, const MultiSprite& p);
  void draw() const;
  void update(Uint32 ticks);
  void goLeft();
  void goRight();
  void goUp();
  void goDown();

private:	
  enum MODE {NORMAL, EVADE};
  IOManager& io;	
  const MultiSprite & enemy;
  static float safeDistance;
  MODE currentMode;
  SmartSprite(const SmartSprite &);
  SmartSprite& operator=(const SmartSprite &rhs);
};
#endif
