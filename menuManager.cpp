#include <cmath>
#include <iostream>
#include <string>
#include <sstream>
#include "menuManager.h"
#include "manager.h"

MenuManager::MenuManager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  screen( IOManager::getInstance().getScreen() ),
  clock( Clock::getInstance() ),
  backColor(),
  menu()
  //numberOfSprites(-1)
{ 
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    throw string("Unable to initialize SDL: ");
  }
  backColor.r = Gamedata::getInstance().getXmlInt("back/red");
  backColor.g = Gamedata::getInstance().getXmlInt("back/green");
  backColor.b = Gamedata::getInstance().getXmlInt("back/blue");
  atexit(SDL_Quit); 
}

void MenuManager::drawBackground() const {
  SDL_FillRect( screen, NULL, 
    SDL_MapRGB(screen->format, backColor.r, backColor.g, backColor.b) );
  SDL_Rect dest = {0, 0, 0, 0};
  SDL_BlitSurface( screen, NULL, screen, &dest );
}

void MenuManager::help() {
  IOManager& io = IOManager::getInstance().getInstance();
  SDL_Event event;
  bool done = false;
  bool nameDone = false;
  const string msg("To win this game you have to make the player reach the other side of the animation.");
  const string msg1("To accomplish this you have to make sure that the player's health status never falls ");
  const string msg2("to zero. On the top-right corner you will find the player's health meter which will");
  const string msg3("keep you updated on its current health status. The player's health will degrade if it");
  const string msg4("collides with green stars. However it can be boosted by making it go over the yellow coins.");
  const string ins("INSTRUCTIONS");
  const string msg5("Press Enter to get back to the menu.");
  io.clearString();
  while ( not done ) {
    Uint8 *keystate = SDL_GetKeyState(NULL);
    if ( SDL_PollEvent(&event) )
    switch (event.type) {
      case SDL_KEYDOWN: {
        if (keystate[SDLK_ESCAPE] || keystate[SDLK_q]) {
          done = true;
        }
        if (keystate[SDLK_RETURN]) {
          nameDone = true;
        }
        io.buildString(event);
      }
    }
    drawBackground();
    io.printStringAfterMessage(ins, 20, 70);
    io.printStringAfterMessage(msg, 20, 120);
    io.printStringAfterMessage(msg1, 20, 140);
    io.printStringAfterMessage(msg2, 20, 160);
    io.printStringAfterMessage(msg3, 20, 180);
    io.printStringAfterMessage(msg4, 20, 200);
    io.printStringAfterMessage(msg5, 20, 250);
    if ( nameDone ) {
      SDL_Flip(screen);
      SDL_Delay(1000);
      done = true;
    }
    if ( !done ) {
      SDL_Flip(screen);
    }
  }
}

void MenuManager::play() {
  //IOManager& io = IOManager::getInstance().getInstance();
  bool keyCatch = false; // To get only 1 key per keydown
  SDL_Event event;
  bool done = false;
  // Here, we need to create an instance of the Manager,
  // the one that manages the game not the menu:
  Manager manager;
  manager.pause();

  while ( not done ) {
    int v;
    drawBackground();
    menu.draw();
    SDL_Flip(screen);

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE :
        case SDLK_q : {
          done = true;
          break;
        }
        case SDLK_RETURN : {
          if ( !keyCatch ) {
            menu.lightOn();
            if ( menu.getIconClicked() == "Start Game" ) {
              manager.unpause();
              while(!manager.getExits()){
                manager.play();
                v = manager.getStopGameFlag();
                // if(v == 1)
                if(!manager.getExits()){ 
                  manager.~Manager();
                  new(&manager) Manager();
                }
                if(v==1){
                  v = 0;
                  menu.lightOff();
                  break;
                  //manager.setExits(true);
                }

              }             
              manager.setExits(false);
              manager.pause();
              
            }
            //if ( menu.getIconClicked() == "Parameters" ) {
              //getNumberOfSprites();
              // After we get the number, we must set it to Manager:
              //manager.setNumberOfSprites( numberOfSprites );
            //}
            if ( menu.getIconClicked() == "Help" ) {
              // Here is where we explain how to play the game"
              help();
              std::cout << "Give help  ..." << std::endl;
            }
            if ( menu.getIconClicked() == "Exit" ) {
              drawBackground();
              menu.draw();
              SDL_Flip(screen);
              SDL_Delay(250);
              done = true;
            }
          }
          break;
        }
        case SDLK_DOWN   : {
          if ( !keyCatch ) {
            menu.increment();
          }
          break;
        }
        case SDLK_UP   : {
          if ( !keyCatch ) {
            menu.decrement();
          }
          break;
        }
        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
      menu.lightOff();
    }
  }
}
