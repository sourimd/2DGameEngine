#ifndef SNOWFLAKESPRITE__H
#define SNOWFLAKESPRITE__H
#include <string>
#include "drawable.h"

class SnowFlakeSprite : public Drawable {
public:
  SnowFlakeSprite(const std::string&, float scaledFactor);
  SnowFlakeSprite(const std::string&, const Vector2f& pos, const Vector2f& vel, float scaledFactor);
  SnowFlakeSprite(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*, float scaledFactor);
  SnowFlakeSprite(const SnowFlakeSprite& s);
  virtual ~SnowFlakeSprite() { } 
  SnowFlakeSprite& operator=(const SnowFlakeSprite&);

  virtual const Frame* getFrame() const { return frame; }
  virtual void draw() const;
  virtual void draw(int angle) const;

  void drawRotateAndScaled(int angle) const;
  float getScaledFactor() const;

  virtual void update(Uint32 ticks);
  virtual int getType() const;
private:
  const Frame * frame;
  int frameWidth;
  int frameHeight;
  int worldWidth;
  int worldHeight;
  int type;
  float scaledFactor;
  int getDistance(const SnowFlakeSprite*) const;
};
#endif
