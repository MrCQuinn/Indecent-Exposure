//
//  power_ups.cpp
//  game2
//
//  Created by Portia Seater on 5/22/16.


#include "items.hpp"
#include "main.hpp"
#include <math.h>


Items::Items(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int h, int w, Environment* passed_environment) //Constructor
{
    environment = passed_environment;
    pickedup = false;
    
    sdl_setup = passed_SDL_Setup;
    
    unit = new Sprite(sdl_setup->GetRenderer(), passed_image, starting_x, starting_y, h, w);
    unit->SetOrigin((unit->GetWidth())/2, (unit->GetHeight())/2);
}


Items::~Items() //Destructor
{
    delete unit;
}

void Items::Draw()
{
    unit->Draw();
}


int Items::getItemX(){
    return unit->GetX();
}

int Items::getItemY(){
    return unit->GetY();
}

int Items::getItemW(){
    return unit->GetWidth();
}

int Items::getItemH(){
    return unit->GetHeight();
}

void Items::pickup(){
    pickedup = true;
}

bool Items::gotten(){
    return pickedup;
}


