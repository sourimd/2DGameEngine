#ifndef MULTISPRITE__H
#define MULTISPRITE__H
#include <string>
#include <vector>
#include "drawable.h"
#include "collisionStrategy.h"

class MultiSprite : public Drawable {

public:
  MultiSprite(const std::string&);
  MultiSprite(const MultiSprite&);
  //virtual ~MultiSprite() { }
  virtual ~MultiSprite() { 
    delete perPixelStrategy;
  } 
  
  virtual void draw() const;
  virtual void draw(int angle) const;
  virtual void update(Uint32 ticks){ std::cout << ticks << std::endl;};
  int up(Uint32 ticks);
  virtual const Frame* getFrame() const { 
    return frames[currentFrame]; 
  }
  virtual int getType() const;

  // bool getRightPressed(){ return rightPressed; }
  // bool getLeftPressed(){ return leftPressed; }

  void setLeftPressed(bool boolval){ leftPressed = boolval;}
  void setRightPressed(bool boolval){ rightPressed = boolval;}
  void setUpPressed(bool boolval){ upPressed = boolval;}
  void setDownPressed(bool boolval){ downPressed = boolval;}
  void setVanish(bool boolval){vanish = boolval; }

  bool collidedWith(const Drawable* d) const {
    return perPixelStrategy->execute(*this, *d);

  }
private:
  MultiSprite& operator=(const MultiSprite&);

protected:
  const std::vector<Frame *> frames;
  int worldWidth;
  int worldHeight;

  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  float timeSinceLastFrame;
  int frameWidth;
  int frameHeight;
  bool left;
  int type;

  //
  bool rightPressed;
  bool leftPressed;
  bool upPressed;
  bool downPressed;
  bool vanish;

  PerPixelCollisionStrategy * perPixelStrategy;

  void advanceFrame(Uint32 ticks);
};
#endif
