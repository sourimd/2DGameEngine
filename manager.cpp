#include <iostream>
#include <string>
#include <iomanip>
#include "multisprite.h"
#include "sprite.h"
#include "snowFlakeSprite.h"
#include "coinSprite.h"
#include "asteroidSprite.h"
#include "smartSprite.h"
#include "gamedata.h"
#include "manager.h"
#include <list>
#include "aaline.h"
#include <ctime>

const int HUD_WIDTH = 200;
const int HUD_HEIGHT = 200;

int Manager::angle = 0;
int Manager::batAngle = 0;

Manager::~Manager() { 
  
  MultiSprite* temp;
  std::list<MultiSprite*>::iterator ptr = sprites.begin(); // <<---------
  while(ptr != sprites.end()){
    temp = (*ptr);
    ++ptr;
    delete temp;
  }

  SnowFlakeSprite* temp1;
  
  std::list<SnowFlakeSprite*>::iterator ptr1 = snowFlakeSprites.begin();
  //ptr1 = snowFlakeSprites.begin();
  while(ptr1 != snowFlakeSprites.end()){
    temp1 = (*ptr1);
    ++ptr1;
    delete temp1;
  }

  AsteroidSprite* temp2;
  
  std::list<AsteroidSprite*>::iterator ptr2 = asteroidSprites.begin();
  while(ptr2 != asteroidSprites.end()){
    temp2 = (*ptr2);
    ++ptr2;
    delete temp2;
  }

  CoinSprite* temp3;
  
  std::list<CoinSprite*>::iterator ptr3 = coinSprites.begin();
  //ptr1 = snowFlakeSprites.begin();
  while(ptr3 != coinSprites.end()){
    temp3 = (*ptr3);
    ++ptr3;
    delete temp3;
  }

  SmartSprite* temp4;
  
  std::list<SmartSprite*>::iterator ptr4 = smartSprites.begin();
  //ptr1 = snowFlakeSprites.begin();
  while(ptr4 != smartSprites.end()){
    temp4 = (*ptr4);
    ++ptr4;
    delete temp4;
  }

}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  sound(),
  bar(),
  barFactor(0),
  win(1),
  stopGameFlag(0),
  gameEndMessage("Game Ongoing"),
  restart(0),
  xit(false),
  screen( io.getScreen() ),
  HUDflag(1),
  curLength(50),
  world("mountains", Gamedata::getInstance().getXmlInt("mountains/factor") ),
  world1("mtdown", Gamedata::getInstance().getXmlInt("mtdown/factor") ),
  world2("mtdown1", Gamedata::getInstance().getXmlInt("mtdown1/factor") ),

  viewport( Viewport::getInstance() ),
  sprites(),
  snowFlakeSprites(),
  coinSprites(),
  asteroidSprites(),
  smartSprites(),
  numberOfSnowFlakes(Gamedata::getInstance().getXmlInt("snowflake/number")),
  
  numberOfAsteroids(Gamedata::getInstance().getXmlInt("star/number")),
  numberOfCoins(Gamedata::getInstance().getXmlInt("coin/number")),

  currentSprite(0),

  makeVideo( false ),
  frameCount( 0 ),
  username(  Gamedata::getInstance().getXmlStr("username") ),
  title( Gamedata::getInstance().getXmlStr("screenTitle") ),
  frameMax( Gamedata::getInstance().getXmlInt("frameMax") )
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  SDL_WM_SetCaption(title.c_str(), NULL);
  atexit(SDL_Quit);
  sprites.push_back( new MultiSprite("bats") );
  //sprites.push_back( new Sprite("star") );

//---------------------------------
  float r;
  float minScale = Gamedata::getInstance().getXmlFloat("snowflake/scale/min");
  float maxScale = Gamedata::getInstance().getXmlFloat("snowflake/scale/max");
  float midScale = (minScale+maxScale)/2;
  
  for(int i=0;i<numberOfSnowFlakes/2;i++){
    r = Gamedata::getInstance().getRandFloat(minScale, midScale); 
    snowFlakeSprites.push_back( new SnowFlakeSprite("snowflake", r));
  }

  for(int i=numberOfSnowFlakes/2;i<numberOfSnowFlakes;i++){
    r = Gamedata::getInstance().getRandFloat(midScale, maxScale);
    snowFlakeSprites.push_back( new SnowFlakeSprite("snowflake", r));
  }

//---------------------------------
  std::list<MultiSprite*>::iterator ptrxy = sprites.begin();
  for(int i=0;i<numberOfAsteroids;i++){
    smartSprites.push_back( new SmartSprite("asteroid", *(*ptrxy) ) );
  }


  for(int i=0;i<numberOfAsteroids;i++){
    //r = Gamedata::getInstance().getRandFloat(midScale, maxScale);
    asteroidSprites.push_back( new AsteroidSprite("star"));
  }

  

  for(int i=0;i<numberOfCoins;i++){
    //r = Gamedata::getInstance().getRandFloat(midScale, maxScale);
    coinSprites.push_back( new CoinSprite("coin", 1));
  }


  //viewport.setObjectToTrack(sprites[currentSprite]);
  int counter; //<<------------
  std::list<MultiSprite*>::iterator ptr2 = sprites.begin();
  for(counter = 0; counter < currentSprite; counter++){
    ++ptr2;
  }
  viewport.setObjectToTrack(*ptr2);

}

void Manager::draw(int HUDflag) {
  world.draw();

  //sort the snow flake sprites here

  for (unsigned i = 0; i < snowFlakeSprites.size()/2; ++i) {
    //sprites[i]->draw();
    unsigned int counter; //<<------------
    std::list<SnowFlakeSprite*>::const_iterator ptr3 = snowFlakeSprites.begin();
    for(counter = 0; counter < i; counter++){
      ++ptr3;
    }
    (*ptr3)->drawRotateAndScaled(getAngle());
   viewport.draw(); 
    
  }
  world2.draw();
  for (unsigned i = snowFlakeSprites.size()/2; i < snowFlakeSprites.size(); ++i) {
    //sprites[i]->draw();
    unsigned int counter; //<<------------
    std::list<SnowFlakeSprite*>::const_iterator ptr3 = snowFlakeSprites.begin();
    for(counter = 0; counter < i; counter++){
      ++ptr3;
    }
    (*ptr3)->drawRotateAndScaled(getAngle());
   viewport.draw(); 
    
  }
  world1.draw();

  for (unsigned i = 0; i < asteroidSprites.size(); ++i) {
    //sprites[i]->draw();
    unsigned int counter; //<<------------
    std::list<AsteroidSprite*>::const_iterator ptr3 = asteroidSprites.begin();
    for(counter = 0; counter < i; counter++){
      ++ptr3;
    }
    (*ptr3)->drawRotateAndScaled(getAngle());
   viewport.draw(); 
  }
   for (unsigned i = 0; i < asteroidSprites.size(); ++i) {
    //sprites[i]->draw();
    unsigned int counter; //<<------------
    std::list<SmartSprite*>::const_iterator ptr3 = smartSprites.begin();
    for(counter = 0; counter < i; counter++){
      ++ptr3;
    }
    (*ptr3)->draw();
   viewport.draw();
    
  }

  for (unsigned i = 0; i < coinSprites.size(); ++i) {
    //sprites[i]->draw();
    unsigned int counter; //<<------------
    std::list<CoinSprite*>::const_iterator ptr3 = coinSprites.begin();
    for(counter = 0; counter < i; counter++){
      ++ptr3;
    }
    (*ptr3)->drawRotateAndScaled(getAngle());
   viewport.draw(); 
    
  }

  for (unsigned i = 0; i < sprites.size(); ++i) {
    //sprites[i]->draw();
    unsigned int counter; //<<------------
    std::list<MultiSprite*>::const_iterator ptr3 = sprites.begin();
    for(counter = 0; counter < i; counter++){
      ++ptr3;
    }
    if((*ptr3)->getType()==0){
      (*ptr3)->draw(getAngle());
    }
    else{
      (*ptr3)->draw(getBatAngle());
    }
    
  }

  if(HUDflag == 1)
    drawHUD(screen, 5, 10);
  bar.draw();
  io.printMessageAt(title, 10, 550);
  SDL_Flip(screen);
}

void Manager::drawHUD(SDL_Surface* screen, int x, int y) {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, x, y+HUD_HEIGHT/2, 
                      x+HUD_WIDTH,y+HUD_HEIGHT/2, 
                      HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, x,y, x+HUD_WIDTH,y, RED);
  Draw_AALine(screen, x+HUD_WIDTH,y, x+HUD_WIDTH,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x+HUD_WIDTH,y+HUD_HEIGHT, x,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x,y+HUD_HEIGHT, x,y, RED);

  io.printMessageValueAt("Seconds: ", clock.getSeconds(), 10, 20);
  io.printMessageValueAt("fps: ", clock.getAvgFps(), 10, 40);
  io.printMessageAt("W", 40, 70);
  io.printMessageAt("A     D", 20, 90);
  io.printMessageAt("X", 40, 110);
  io.printMessageAt("Press V-> disappear", 10, 140);
  io.printMessageAt("Press V -> reappear", 10, 160);
  io.printMessageAt("Press R -> reset", 10, 180);
}

void Manager::drawHUDGameStop(SDL_Surface* screen, int x, int y, std::string msg) {
  const Uint32 RED = SDL_MapRGB(screen->format, 0xff, 0, 0);
  Draw_AALine(screen, x, y+HUD_HEIGHT/2, 
                      x+HUD_WIDTH,y+HUD_HEIGHT/2, 
                      HUD_HEIGHT, 0xff, 0xff, 0xff, 0xff/2);
  Draw_AALine(screen, x,y, x+HUD_WIDTH,y, RED);
  Draw_AALine(screen, x+HUD_WIDTH,y, x+HUD_WIDTH,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x+HUD_WIDTH,y+HUD_HEIGHT, x,y+HUD_HEIGHT, RED);
  Draw_AALine(screen, x,y+HUD_HEIGHT, x,y, RED);
  
  io.printMessageAt("Game Over", 450, 250);
  io.printMessageAt(msg, 450, 280);
}

int Manager::getAngle(){
    if(angle > 360) angle = angle - 360;
    if(angle < 360) angle = angle + 360;
    angle = angle + Gamedata::getInstance().getXmlInt("star/angleIncrement");
    return angle;
    //return 0;
}

int Manager::getBatAngle(){
  return batAngle;
}

void Manager::makeFrame() {
  std::stringstream strm;
  strm << "frames/" << username<< '.' 
       << std::setfill('0') << std::setw(4) 
       << frameCount++ << ".bmp";
  std::string filename( strm.str() );
  std::cout << "Making frame: " << filename << std::endl;
  SDL_SaveBMP(screen, filename.c_str());
}

void Manager::update() {
  ++clock;
  Uint32 ticks = clock.getElapsedTicks();
  if(clock.getSeconds() == 3){
    HUDflag = 0;
  }
  for (unsigned int i = 0; i < sprites.size(); ++i) {
    //sprites[i]->update(ticks);
    unsigned int counter; //<<------------
    std::list<MultiSprite*>::iterator ptr3 = sprites.begin();
    for(counter = 0; counter < i; counter++){
      ++ptr3;
    }
    stopGameFlag = dynamic_cast<MultiSprite*>(*ptr3)->up(ticks);
  }

  //-----------------
  for (unsigned int i = 0; i < snowFlakeSprites.size(); ++i) {
    //sprites[i]->update(ticks);
    unsigned int counter1; //<<------------
    std::list<SnowFlakeSprite*>::iterator ptr3 = snowFlakeSprites.begin();
    for(counter1 = 0; counter1 < i; counter1++){
      ++ptr3;
    }
    (*ptr3)->update(ticks);
  }

  for (unsigned int i = 0; i < asteroidSprites.size(); ++i) {
    //sprites[i]->update(ticks);
    unsigned int counter1; //<<------------
    std::list<AsteroidSprite*>::iterator ptr3 = asteroidSprites.begin();
    for(counter1 = 0; counter1 < i; counter1++){
      ++ptr3;
    }
    (*ptr3)->update(ticks);
  }

  for (unsigned int i = 0; i < asteroidSprites.size(); ++i) {
    //sprites[i]->update(ticks);
    unsigned int counter1; //<<------------
    std::list<SmartSprite*>::iterator ptr3 = smartSprites.begin();
    for(counter1 = 0; counter1 < i; counter1++){
      ++ptr3;
    }
    (*ptr3)->update(ticks);
  }

  for (unsigned int i = 0; i < coinSprites.size(); ++i) {
    //sprites[i]->update(ticks);
    unsigned int counter1; //<<------------
    std::list<CoinSprite*>::iterator ptr3 = coinSprites.begin();
    for(counter1 = 0; counter1 < i; counter1++){
      ++ptr3;
    }
    (*ptr3)->update(ticks);
  }


  //-------------------------


  if ( makeVideo && frameCount < frameMax ) {
    makeFrame();
  }
  world.update();
  world2.update();
  world1.update();
  curLength = bar.update(ticks, barFactor);
  viewport.update(); // always update viewport last
  if(curLength == 0){
    //end the game
    win = 0;
    stopGameFlag = 1;
  }
}

bool Manager::checkForCollisions() const {
   std::list<MultiSprite*>::const_iterator thebat = sprites.begin();
   std::list<AsteroidSprite*>::const_iterator ptr9 = asteroidSprites.begin();
   while ( ptr9 != asteroidSprites.end() ) {
    if ( (*thebat)->collidedWith(*ptr9) ) return true;
    ++ptr9;
  }
  return false;
}

bool Manager::checkForCoinCollisions() {
   std::list<MultiSprite*>::const_iterator thebat = sprites.begin();
   std::list<CoinSprite*>::iterator ptr9 = coinSprites.begin();
   while ( ptr9 != coinSprites.end() ) {
    if ( (*thebat)->collidedWith(*ptr9) ){
      ptr9 = coinSprites.erase(ptr9);
      return true;
    }
    else{
      ++ptr9;
    } 
    
  }
  return false;
}

void Manager::play() {
  //int HUDflag = 1;
  int a = 0;
  int timeKeeperGameStop;
  SDL_Event event;
  char thekey;
  int coinfactor, starfactor;
  bool done = false;
  bool keyCatch = false;
  while ( not done ) {
    if(stopGameFlag == 1){
      //gameEndMessage = "Game End";
      //clock.pause();
      timeKeeperGameStop = clock.getSeconds();
      a = 1;
      clock.pause();
      while(a==1){
        clock.unpause();
        //io.printMessageAt("Game Over", 400, 400);
        if(win == 0){
          drawHUDGameStop(screen , 400, 200, "You Loose");
        }
        else{
          drawHUDGameStop(screen , 400, 200, "You Win!!");
        }
        
        SDL_Flip(screen);
        if( (clock.getSeconds() - timeKeeperGameStop)>2 ){
          a=0;
        }
      }
      break;
    }
      
    coinfactor = starfactor = 0;
    if(checkForCollisions()){
      starfactor = 10;
    }
    if(checkForCoinCollisions()){
      coinfactor = -10;
    }
    barFactor = starfactor + coinfactor;
    SDL_PollEvent(&event);
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if (event.type ==  SDL_QUIT) { done = true; break; }
    
    if(event.type == SDL_KEYUP) { 
      if (thekey=='w' && keyCatch) {
        keyCatch = false;
        std::list<MultiSprite*>::iterator ptr7 = sprites.begin();
        //thekey='w';
        batAngle = batAngle - 20;
        (*ptr7)->setUpPressed(false);
        thekey='\0';
      }

      if (thekey=='x' && keyCatch) {
        keyCatch = false;
        std::list<MultiSprite*>::iterator ptr7 = sprites.begin();
        //thekey='w';
        batAngle = batAngle + 20;
        (*ptr7)->setDownPressed(false);
        thekey='\0';
      }
      if (thekey=='v' && keyCatch) {
        keyCatch = false;
        std::list<MultiSprite*>::iterator ptr7 = sprites.begin();
        
        (*ptr7)->setVanish(false);
        thekey='\0';
      }
      if (thekey=='a' && keyCatch) {
        keyCatch = false;
        thekey='\0';
      }
      if (thekey=='d' && keyCatch) {
        keyCatch = false;
        thekey='\0';
      }
      if (thekey=='f' && keyCatch) {
        keyCatch = false;
        thekey='\0';
      }
      if (thekey=='s' && keyCatch) {
        keyCatch = false;
        thekey='\0';
      }
      if (thekey=='p' && keyCatch) {
        keyCatch = false;
        thekey='\0';
      }
      if (thekey=='r' && keyCatch) {
        keyCatch = false;
        thekey='\0';
      }

      
    }
    
    if(event.type == SDL_KEYDOWN) {
              if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
                xit = true;
                done = true;
                break;
              }
      
              if (keystate[SDLK_s] && !keyCatch) {
                thekey='s';
                keyCatch = true;
                clock.toggleSloMo();
              }
              if (keystate[SDLK_F1] && !keyCatch) {
                keyCatch = true;
                thekey='f';
                if(HUDflag == 0)
                      HUDflag = 1;
                else
                      HUDflag = 0;
                
              }
              //left pressed
              if (keystate[SDLK_a] && !keyCatch) {
                keyCatch = true;
                thekey = 'a';
                // set leftPressed to true
                std::list<MultiSprite*>::iterator ptr6 = sprites.begin();
                (*ptr6)->setLeftPressed(true);
                (*ptr6)->setRightPressed(false);
              }
              if (keystate[SDLK_d] && !keyCatch) {
                keyCatch = true;
                thekey = 'd';
                // set rightPressed to true
                std::list<MultiSprite*>::iterator ptr7 = sprites.begin();
                (*ptr7)->setRightPressed(true);
                (*ptr7)->setLeftPressed(false);
              }

              if (keystate[SDLK_w] && !keyCatch) {
                keyCatch = true;
                // set rightPressed to true
                std::list<MultiSprite*>::iterator ptr7 = sprites.begin();
                thekey='w';
                batAngle = batAngle + 20;
                (*ptr7)->setUpPressed(true);
                //(*ptr7)->setLeftPressed(false);
              }

              if (keystate[SDLK_v] && !keyCatch) {
                keyCatch = true;
                // set rightPressed to true
                std::list<MultiSprite*>::iterator ptr7 = sprites.begin();
                thekey='v';
                //batAngle = batAngle + 20;
                (*ptr7)->setVanish(true);
                //(*ptr7)->setLeftPressed(false);
              }

              if (keystate[SDLK_x] && !keyCatch) {
                keyCatch = true;
                // set rightPressed to true
                std::list<MultiSprite*>::iterator ptr7 = sprites.begin();
                thekey='x';
                batAngle = batAngle - 20;
                (*ptr7)->setDownPressed(true);
                //(*ptr7)->setLeftPressed(false);
              }
      
              if (keystate[SDLK_p] && !keyCatch) {
                thekey='p';
                keyCatch = true;
                if ( clock.isPaused() ) clock.unpause();
                else clock.pause();
              }
              if (keystate[SDLK_r] && !keyCatch) {
                thekey='r';
                keyCatch = true;
                //restart = 1;
                return;
              }
              if (keystate[SDLK_F4] && !makeVideo) {
                std::cout << "Making video frames" << std::endl;
                makeVideo = true;
              }
    }

    draw(HUDflag);
    update();
  }
}
