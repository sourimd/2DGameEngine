#ifndef COINSPRITE__H
#define COINSPRITE__H
#include <string>
#include "drawable.h"

class CoinSprite : public Drawable {
public:
  CoinSprite(const std::string&, float scaledFactor);
  CoinSprite(const std::string&, const Vector2f& pos, const Vector2f& vel, float scaledFactor);
  CoinSprite(const std::string&, 
         const Vector2f& pos, const Vector2f& vel, const Frame*, float scaledFactor);
  CoinSprite(const CoinSprite& s);
  virtual ~CoinSprite() { } 
  CoinSprite& operator=(const CoinSprite&);

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
  int getDistance(const CoinSprite*) const;
};
#endif
