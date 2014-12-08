#include "SDL/SDL_rotozoom.h"
#include "drawable.h"
#include "frame.h"
#include "ioManager.h"
#include "viewport.h"

Frame::Frame( const std::string& name, SDL_Surface* surf ) : 
  screen(IOManager::getInstance().getScreen()),
  surface( surf ),
  width(Gamedata::getInstance().getXmlInt(name+"/width")), 
  height(Gamedata::getInstance().getXmlInt(name+"/height")),
  sourceX(0),
  sourceY(0)
{ }

Frame::Frame( SDL_Surface* spr, Uint16 w, Uint16 h,
              Sint16 src_x, Sint16 src_y) :
  screen(IOManager::getInstance().getScreen()),
  surface(spr), 
  width(w), height(h),
  sourceX(src_x), sourceY(src_y) {
}

Frame::Frame( const Frame& frame ) :
  screen(frame.screen),
  surface(frame.surface), 
  width(frame.width), 
  height(frame.height),
  sourceX(frame.sourceX), 
  sourceY(frame.sourceY) 
  { }


Frame& Frame::operator=(const Frame& rhs) {
  surface = rhs.surface;
  screen = rhs.screen;
  width = rhs.width;
  height = rhs.height;
  sourceX = rhs.sourceX;
  sourceY = rhs.sourceY;
  return *this;
}

void Frame::draw(Sint16 x, Sint16 y) const {
  SDL_Rect src = { sourceX, sourceY, width, height };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, width, height };
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 sx, Sint16 sy, Sint16 dx, Sint16 dy) const {
  SDL_Rect src = { sx, sy, width, height };    
  SDL_Rect dest = {dx, dy, width, height };
  SDL_BlitSurface(surface, &src, screen, &dest);
}

void Frame::draw(Sint16 x, Sint16 y, double angle) const {
  SDL_Surface* tmp = rotozoomSurface(surface, angle, 1, 1);
  Sint16 zero = 0;
  Uint16 width = tmp->w;
  Uint16 height = tmp->h;
  SDL_Rect src = { zero, zero, width, height };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(tmp, &src, screen, &dest);
  SDL_FreeSurface( tmp );
}

void Frame::drawRotateAndScaled(Sint16 x, Sint16 y, double angle, float scaledFactor) const {
  SDL_Surface* tmp = rotozoomSurface(surface, angle, 1, 1);
  SDL_Surface* scaledSurface = rotozoomSurface(tmp, 0, scaledFactor, SMOOTHING_ON);
  
  Sint16 zero = 0;
  Uint16 width = scaledSurface->w;
  Uint16 height = scaledSurface->h;
  SDL_Rect src = { zero, zero, width, height };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(scaledSurface, &src, screen, &dest);
  SDL_FreeSurface( scaledSurface );
  SDL_FreeSurface( tmp );
}

void Frame::vanish(Sint16 x, Sint16 y, float scaledFactor) const {
  SDL_Surface* scaledSurface = rotozoomSurface(surface, 0, scaledFactor, SMOOTHING_ON);
  
  Sint16 zero = 0;
  Uint16 width = scaledSurface->w;
  Uint16 height = scaledSurface->h;
  SDL_Rect src = { zero, zero, width, height };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(scaledSurface, &src, screen, &dest);
  SDL_FreeSurface( scaledSurface );
  
}

void Frame::drawLeft(Sint16 x, Sint16 y, double angle) const {
  SDL_Surface* tmp1 = rotozoomSurface(surface, angle, 1, 1);
  SDL_Surface* tmp = rotozoomSurfaceXY(tmp1, 0, -1, 1,0);
  
  Sint16 zero = 0;
  Uint16 width = tmp->w;
  Uint16 height = tmp->h;
  SDL_Rect src = { zero, zero, width, height };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(tmp, &src, screen, &dest);
  SDL_FreeSurface( tmp );
}
void Frame::drawLeft(Sint16 x, Sint16 y) const {
  SDL_Surface* tmp = rotozoomSurfaceXY(surface, 0, -1, 1,0);
  //tmp = rotozoomSurface(tmp, angle, 1, 1);
  Sint16 zero = 0;
  Uint16 width = tmp->w;
  Uint16 height = tmp->h;
  SDL_Rect src = { zero, zero, width, height };    
  x -= Viewport::getInstance().X();
  y -= Viewport::getInstance().Y();
  SDL_Rect dest = {x, y, 0, 0 };
  SDL_BlitSurface(tmp, &src, screen, &dest);
  SDL_FreeSurface( tmp );
}

