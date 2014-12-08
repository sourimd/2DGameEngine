#include <cmath>
#include "coinSprite.h"
#include "gamedata.h"
#include "frameFactory.h"

int getRF(){
  int randNumber = Gamedata::getInstance().getRandInRange(10,700);
  randNumber *= rand() % 2 ? -1 : 1;
  return randNumber;
}

int getPRF(){
  int randNumber = Gamedata::getInstance().getRandInRange(10,5000);
  randNumber *= rand() % 2 ? -1 : 1;
  return randNumber;
}



CoinSprite::CoinSprite(const std::string& name, float scaledFactor) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x") + getPRF(), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y") + getRF()), 
           Vector2f((Gamedata::getInstance().getXmlInt(name+"/speedX")), 
                    (Gamedata::getInstance().getXmlInt(name+"/speedY"))) 
           ),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2),
  scaledFactor(scaledFactor)
{ }

CoinSprite::CoinSprite(const string& n, const Vector2f& pos, const Vector2f& vel, float scaledFactor):
  Drawable(n, pos, vel), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2),
  scaledFactor(scaledFactor)
{ }

CoinSprite::CoinSprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm, float scaledFactor):
  Drawable(n, pos, vel), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2),
  scaledFactor(scaledFactor)
{ }

CoinSprite::CoinSprite(const CoinSprite& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2),
  scaledFactor(s.scaledFactor)
{ }

CoinSprite& CoinSprite::operator=(const CoinSprite& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void CoinSprite::drawRotateAndScaled(int angle) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->drawRotateAndScaled(x, y, angle, scaledFactor); 
}

float CoinSprite::getScaledFactor() const {
  return scaledFactor;
}

void CoinSprite::draw(int angle) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y, angle); 
}

void CoinSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

int CoinSprite::getDistance(const CoinSprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void CoinSprite::update(Uint32 ticks) { 
  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr);

  if ( Y() < 0) {
    velocityY( abs( velocityY() ) );
  }
  if ( Y() > worldHeight-frameHeight) {
    Y(0.0);
    //velocityY( -abs( velocityY() ) );
  }

  if ( X() < 0) {
    velocityX( abs( velocityX() ) );
  }
  if ( X() > worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
  }  
}

int CoinSprite::getType() const{
  return type;
}
