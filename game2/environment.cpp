#include "environment.hpp"
#include "main.hpp"

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, Main* passed_main)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    main = passed_main;
    startTime = SDL_GetTicks()/1000; //ensures game time corresponds to when spacebar hit on splash screen and game begins
    
    characterImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/character.png");
    character = new Character(sdl_setup, characterImage, 300, 200, MouseX, MouseY, this);
    
}

Environment::~Environment()
{
    delete character;
}

void Environment::DrawBack()
{
    character->Draw();
}

void Environment::Update()
{
    
    character->Update();
}


//void Environment::setCollisionImage(Sprite* building)
//{
//    building->setCollisionImage(collisionImage20);
//}

//void Environment::endGame(int loser) //tells Main game is over and declares winner
//{
//    main->endGame(loser);
//}
