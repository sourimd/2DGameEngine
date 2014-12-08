#include <vector>
#include <SDL.h>
#include "ioManager.h"
#include "clock.h"
#include "world.h"
#include "viewport.h"
#include <list>
#include "snowFlakeSprite.h"
#include "coinSprite.h"
#include "asteroidSprite.h"
#include "smartSprite.h"
#include "multisprite.h"
#include "sound.h"
#include "health.h"



class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  void pause() { clock.pause(); }
  void unpause() { clock.unpause(); }
  
  int getStopGameFlag() const { return stopGameFlag;}
  void setStopGameFlag(int i){stopGameFlag = i;}
  
  std::string getGameEndMessage() const { return gameEndMessage;}
  void setGameEndMessage(std::string msg) {gameEndMessage = msg;}

  void setRestart(int i){restart = i;}
  int getRestart(){ return restart;}

  void setExits(bool b){xit = b;}
  bool getExits(){return xit;}

  static int getAngle();
  static int getBatAngle();

private:
  static int angle;
  static int batAngle;

  const bool env;
  const IOManager& io;
  Clock& clock;
  SDLSound sound;
  Health bar;
  int barFactor;
  int win;
  int stopGameFlag;
  std::string gameEndMessage;
  int restart;
  bool xit;

  SDL_Surface * const screen;
  int HUDflag;
  int curLength;
  World world, world1, world2;
  Viewport& viewport;

  std::list<MultiSprite*> sprites;
  
  std::list<SnowFlakeSprite*> snowFlakeSprites;
  std::list<CoinSprite*> coinSprites;
  std::list<AsteroidSprite*> asteroidSprites;
  std::list<SmartSprite*> smartSprites;
  int numberOfSnowFlakes;
  int numberOfAsteroids;
  int numberOfCoins;
  
  int currentSprite;

  bool makeVideo;
  int frameCount;
  const std::string username;
  const std::string title;
  const int frameMax;

  //void draw() const;
  void draw(int);
  void drawHUD(SDL_Surface* , int, int);//check if u can make it const
  void drawHUDGameStop(SDL_Surface* , int, int, std::string);
  void update();
  bool checkForCollisions() const;
  bool checkForCoinCollisions();
  Manager(const Manager&);
  Manager& operator=(const Manager&);
  void makeFrame();
};
