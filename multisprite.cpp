#include "multisprite.h"
#include "gamedata.h"
#include "frameFactory.h"


void MultiSprite::advanceFrame(Uint32 ticks) {
	timeSinceLastFrame += ticks;
	if (timeSinceLastFrame > frameInterval) {
    currentFrame = (currentFrame+1) % numberOfFrames;
		timeSinceLastFrame = 0;
	}
}



MultiSprite::MultiSprite( const std::string& name) :
  
  Drawable(name, 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/startLoc/x"), 
                    Gamedata::getInstance().getXmlInt(name+"/startLoc/y")), 
           Vector2f(Gamedata::getInstance().getXmlInt(name+"/speedX"),
                    Gamedata::getInstance().getXmlInt(name+"/speedY"))
           ),
  frames( FrameFactory::getInstance().getFrames(name) ),
  worldWidth(Gamedata::getInstance().getXmlInt("world/width")),
  worldHeight(Gamedata::getInstance().getXmlInt("world/height")),
  
  currentFrame(0),
  numberOfFrames( Gamedata::getInstance().getXmlInt(name+"/frames") ),
  frameInterval( Gamedata::getInstance().getXmlInt(name+"/frameInterval") ),
  timeSinceLastFrame( 0 ),
  frameWidth(frames[0]->getWidth()),
  frameHeight(frames[0]->getHeight()),
  left(0),
  type(1),
  rightPressed(false),
  leftPressed(false),
  upPressed(false),
  downPressed(false),
  vanish(false),
  perPixelStrategy(NULL)
  
{ }

MultiSprite::MultiSprite(const MultiSprite& s) :
  
  Drawable(s), 
  frames(s.frames),
  worldWidth( s.worldWidth ),
  worldHeight( s.worldHeight ),
  
  currentFrame(s.currentFrame),
  numberOfFrames( s.numberOfFrames ),
  frameInterval( s.frameInterval ),
  timeSinceLastFrame( s.timeSinceLastFrame ),
  frameWidth( s.frameWidth ),
  frameHeight( s.frameHeight ),
  left(s.left),
  type(s.type),
  rightPressed(s.rightPressed),
  leftPressed(s.leftPressed),
  upPressed(s.upPressed),
  downPressed(s.downPressed),
  vanish(s.vanish),
  perPixelStrategy(s.perPixelStrategy)
  {
    perPixelStrategy = new PerPixelCollisionStrategy;
  }

void MultiSprite::draw() const { 
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if(left)
    frames[currentFrame]->drawLeft(x, y);
  else
    frames[currentFrame]->draw(x, y);
}

void MultiSprite::draw(int batAngle) const {
  Uint32 x = static_cast<Uint32>(X());
  Uint32 y = static_cast<Uint32>(Y());
  if( Y()<0 or Y()>worldHeight-frameHeight )
    batAngle = 0;
  if(vanish){
    frames[currentFrame]->vanish(x, y, 0.00000000000000000000001);
  }
  else{
      if(left)
        frames[currentFrame]->drawLeft(x, y, batAngle);
      else
        frames[currentFrame]->draw(x, y, batAngle);
  }
}

int MultiSprite::up(Uint32 ticks) {
  int flag = 0;
  if(upPressed and Y()>0){
    velocityY(-100);
  }
  else if (upPressed and Y() <= 0){
    velocityY(0);
  }

  if(downPressed and Y() < worldHeight-frameHeight){
    velocityY(100);
  }
  else if (downPressed and Y() >= worldHeight-frameHeight){
    velocityY(0);
  }
  if(not downPressed and not upPressed){
    velocityY(0);
  }

  if ( X() < 0 ) {
    velocityX( abs( velocityX() ) );
    left = 0;
    rightPressed = false;
    leftPressed = false;
  }
  if ( X() > worldWidth-frameWidth ) {
    velocityX( -abs( velocityX() ) );
    left = 1;
    rightPressed = false;
    leftPressed = false;
    flag = 1;
    //std::cout << numberOfFrames/2 << std::endl;
  }

  if ( leftPressed and X()>0 and X() < worldWidth-frameWidth) {
    velocityX( -abs( velocityX() ) );
    left = 1;
    rightPressed = false;
    //std::cout << numberOfFrames/2 << std::endl;
  }

  if ( rightPressed and X()>0 and X() < worldWidth-frameWidth) {
    velocityX( abs( velocityX() ) );
    left = 0;
    leftPressed = false;
  }

  advanceFrame(ticks);

  Vector2f incr = getVelocity() * static_cast<float>(ticks) * 0.001;
  setPosition(getPosition() + incr); 
  return flag; 

}

int MultiSprite::getType() const{
  return type;
}
