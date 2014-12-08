#ifndef ASTEROIDSPRITE__H
#define ASTEROIDSPRITE__H
#include <string>
#include "drawable.h"

class AsteroidSprite : public Drawable {
public:
  AsteroidSprite(const std::string&);
  AsteroidSprite(const std::string&, const Vector2f& pos, const Vector2f& vel);
  AsteroidSprite(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*);
  AsteroidSprite(const AsteroidSprite& s);
  virtual ~AsteroidSprite() { } 
  AsteroidSprite& operator=(const AsteroidSprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void draw(int angle) const;

  void drawRotateAndScaled(int angle) const;
  //float getScaledFactor() const;

  virtual void update(Uint32 ticks);
  virtual int getType() const;
private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int type;
  int getDistance(const AsteroidSprite*) const;
};
#endif
