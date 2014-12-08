#include <cmath>
#include "asteroidSprite.h"
#include "gamedata.h"
#include "frameFactory.h"

int getRFactor(){
  int randNumber = Gamedata::getInstance().getRandInRange(10,200);
  randNumber *= rand() % 2 ? -1 : 1;
  return randNumber;
}

int getPosiRandomFactor(){
  int randNumber = Gamedata::getInstance().getRandInRange(10,5000);
  randNumber *= rand() % 2 ? -1 : 1;
  return randNumber;
}



AsteroidSprite::AsteroidSprite(const std::string& name) :
  Drawable(name,
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x") + getPosiRandomFactor(), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f((Gamedata::getInstance().getXmlInt(name+"/speedX") + getRFactor()), 
                    (Gamedata::getInstance().getXmlInt(name+"/speedY") + getRFactor())) 
           ),
  frame( FrameFactory::getInstance().getFrame(name) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2)
{ }

AsteroidSprite::AsteroidSprite(const string& n, const Vector2f& pos, const Vector2f& vel):
  Drawable(n, pos, vel), 
  frame( FrameFactory::getInstance().getFrame(n) ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2)
{ }

AsteroidSprite::AsteroidSprite(const string& n, const Vector2f& pos, const Vector2f& vel,
               const Frame* frm):
  Drawable(n, pos, vel), 
  frame( frm ),
  frameWidth(frame->getWidth()),
  frameHeight(frame->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2)
{ }

AsteroidSprite::AsteroidSprite(const AsteroidSprite& s) :
  Drawable(s), 
  frame(s.frame),
  frameWidth(s.getFrame()->getWidth()),
  frameHeight(s.getFrame()->getHeight()),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  type(2)
{ }

AsteroidSprite& AsteroidSprite::operator=(const AsteroidSprite& rhs) {
  Drawable::operator=( rhs );
  frame = rhs.frame;
  frameWidth = rhs.frameWidth;
  frameHeight = rhs.frameHeight;
  worldWidth = rhs.worldWidth;
  worldHeight = rhs.worldHeight;
  return *this;
}

void AsteroidSprite::drawRotateAndScaled(int angle) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->drawRotateAndScaled(x, y, angle, 1); 
}

// float AsteroidSprite::getScaledFactor() const {
//   return scaledFactor;
// }

void AsteroidSprite::draw(int angle) const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y, angle); 
}

void AsteroidSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  frame->draw(x, y); 
}

int AsteroidSprite::getDistance(const AsteroidSprite *obj) const { 
  return hypot(X()-obj->X(), Y()-obj->Y());
}

void AsteroidSprite::update(Uint32 ticks) { 
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

int AsteroidSprite::getType() const{
  return type;
}
