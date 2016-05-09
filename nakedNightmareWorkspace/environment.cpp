#include "environment.hpp"
#include "main.hpp"

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, Main* passed_main)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    main = passed_main;
    startTime = SDL_GetTicks()/1000; //ensures game time corresponds to when spacebar hit on splash screen and game begins
    
}

Environment::~Environment()
{
    
}

void Environment::DrawBack()
{

}

void Environment::Update()
{
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){ //toggle showing of menu
        if(sdl_setup->GetEv()->key.keysym.sym == SDLK_SPACE){
            if(showMenu){
                showMenu = false;
            }else{
                showMenu = true;
            }
        }
    }
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
        if(sdl_setup->GetEv()->key.keysym.sym == SDLK_DOWN){
            //MOVE CHARACTER DOWN
        }
    }
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
        if(sdl_setup->GetEv()->key.keysym.sym == SDLK_UP){
            //MOVE CHARACTER UP
        }
    }
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
        if(sdl_setup->GetEv()->key.keysym.sym == SDLK_LEFT){
            //MOVE CHARACTER LEFT
        }
    }
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
        if(sdl_setup->GetEv()->key.keysym.sym == SDLK_RIGHT){
            //MOVE CHARACTER RIGHT
        }
    }
}


//void Environment::setCollisionImage(Sprite* building)
//{
//    building->setCollisionImage(collisionImage20);
//}

//void Environment::endGame(int loser) //tells Main game is over and declares winner
//{
//    main->endGame(loser);
//}
