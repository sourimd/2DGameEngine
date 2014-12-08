#include <cmath>
#include "viewport.h"
#include "smartSprite.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}
int getRandomFactorSmart(){
  int randNumber = Gamedata::getInstance().getRandInRange(10,200);
  randNumber *= rand() % 2 ? -1 : 1;
  return randNumber;
}

int getPositionRandomFactorSmart(){
  int randNumber = Gamedata::getInstance().getRandInRange(10,5000);
  randNumber *= rand() % 2 ? -1 : 1;
  return randNumber;
}


SmartSprite::SmartSprite(const std::string& name, const MultiSprite& p) :
 Sprite(name, Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x") + getPositionRandomFactorSmart(), 
                       Gamedata::getInstance().getXmlInt(name+"/startLoc/y")+ getPositionRandomFactorSmart()), 
   Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX") + getRandomFactorSmart(), 
            Gamedata::getInstance().getXmlInt(name+"/speedY") + getRandomFactorSmart())
 ), 
 io(IOManager::getInstance()), 
 enemy(p), 
 currentMode(NORMAL) 
{ }

void SmartSprite::goLeft()  { 
  if (X() > 0) velocityX( -abs(velocityX()) ); 
}
void SmartSprite::goRight() { velocityX( fabs(velocityX()) ); }
void SmartSprite::goUp()    { velocityY( -fabs(velocityY()) ); }
void SmartSprite::goDown()  { velocityY( fabs(velocityY()) ); }

void SmartSprite::draw() const {
  Sprite::draw();
  int x = 10+ X() - Viewport::getInstance().X();
  int y = 10+ Y() - Viewport::getInstance().Y();
  std::stringstream strm;
  strm << currentMode;
  //io.printMessageBlackAt( strm.str(), x, y); 
}

void SmartSprite::update(Uint32 ticks) {
  Sprite::update(ticks);
  float x= X()+getFrame()->getWidth()/2;
  float y= Y()+getFrame()->getHeight()/2;
  float ex= enemy.X()+enemy.getFrame()->getWidth()/2;
  float ey= enemy.Y()+enemy.getFrame()->getHeight()/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < 100) currentMode = EVADE;
  }
  else if  ( currentMode == EVADE ) {
    if(distanceToEnemy > 100) currentMode = NORMAL;
    else {
      if ( x < ex ) goLeft();
      if ( x > ex ) goRight();
      if ( y < ey ) goUp();
      if ( y > ey ) goDown();
    }
  }
}

