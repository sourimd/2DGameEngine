#include <cmath>
#include "snowFlakeSprite.h"
#include "gamedata.h"
#include "frameFactory.h"

int getRandomFactor(){
  int randNumber = Gamedata::getInstance().getRandInRange(10,200);
  randNumber *= rand() % 2 ? -1 : 1;
  return randNumber;
}

int getPositionRandomFactor(){
  int randNumber = Gamedata::getInstance().getRandInRange(10,5000);
  randNumber *= rand() % 2 ? -1 : 1;
  return randNumber;
}



SnowFlakeSprite::SnowFlakeSprite(const std::string& name, float scaledFactor) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x") + getPositionRandomFactor(), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f((Gamedata::getInstance().getXmlInt(name+"/speedX") + getRandomFactor())*scaledFactor, 
                    (Gamedata::getInstance().getXmlInt(name+"/speedY") + getRandomFactor())*scaledFactor) 
           ),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2),
  scaledFactor(scaledFactor)
{ }

SnowFlakeSprite::SnowFlakeSprite(const string& n, const Vector2f& pos, const Vector2f& vel, float scaledFactor):
  Drawable(n, pos, vel), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2),
  scaledFactor(scaledFactor)
{ }

SnowFlakeSprite::SnowFlakeSprite(const string& n, const Vector2f& pos, const Vector2f& vel,
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

SnowFlakeSprite::SnowFlakeSprite(const SnowFlakeSprite& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2),
  scaledFactor(s.scaledFactor)
{ }

SnowFlakeSprite& SnowFlakeSprite::operator=(const SnowFlakeSprite& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void SnowFlakeSprite::drawRotateAndScaled(int angle) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->drawRotateAndScaled(x, y, angle, scaledFactor); 
}

float SnowFlakeSprite::getScaledFactor() const {
  return scaledFactor;
}

void SnowFlakeSprite::draw(int angle) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y, angle); 
}

void SnowFlakeSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

int SnowFlakeSprite::getDistance(const SnowFlakeSprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void SnowFlakeSprite::update(Uint32 ticks) { 
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

int SnowFlakeSprite::getType() const{
  return type;
}
