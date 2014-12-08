#include "health.h"

Health::Health() :
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(750, 50)), 
  totalLength(50), 
  currentLength(50), 
  thick(14), 
  //increments(20),
  interval(1000),
  deltaTime(0),
  RED( SDL_MapRGB(screen->format, 0xff, 0x00, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xce, 0xb4, 0xb4) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
  color(RED) {
}

Health::Health(int sx, int sy, int tl, int cl,
               float t, Uint32 c, float sp):
  screen(IOManager::getInstance().getScreen()),
  start(Vector2f(sx, sy)), 
  totalLength(tl), 
  currentLength(cl), 
  thick(t), 
  //increments(inc),
  interval(sp),
  deltaTime(SDL_GetTicks()),
  RED( SDL_MapRGB(screen->format, 0xff, 0x00, 0x00) ),
  GRAY( SDL_MapRGB(screen->format, 0xff, 0xff, 0xff) ),
  BLACK( SDL_MapRGB(screen->format, 0x00, 0x00, 0x00) ),
    color(c) {
}

void Health::drawBox() const {
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+totalLength, start[1], 
                      thick, GRAY);
  // Two Horizontal lines
  Draw_AALine(screen, start[0], start[1]-8, 
                      start[0]+totalLength, start[1]-8, 
                      1.0, BLACK);
  Draw_AALine(screen, start[0], start[1]+8, 
                      start[0]+totalLength, start[1]+8, 
                      1.0, BLACK);
  // Two Vertical lines
  Draw_AALine(screen, start[0]-1, start[1]-8, 
                      start[0]-1, start[1]+8, 
                      2.0, BLACK);
  Draw_AALine(screen, start[0]+totalLength+1, start[1]-8, 
                      start[0]+totalLength+1, start[1]+8, 
                      2.0, BLACK);
}

void Health::draw() const {
  IOManager::getInstance().printMessageAt("Bat's Health", 725, 14);
  drawBox();
  Draw_AALine(screen, start[0], start[1], 
                      start[0]+currentLength, start[1], 
                      thick, color);
}
int Health::update(Uint32 ticks, int increments) {
  deltaTime += ticks;
  if(currentLength == 50 and increments < 0) return -1;
  if(currentLength == 0 and increments > 0) return -1;
  if ( currentLength >= 0 && currentLength <= 50 && deltaTime > interval ) {
    deltaTime = 0;
    currentLength -= increments;
    return currentLength;
  }
}
