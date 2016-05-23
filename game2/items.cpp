//
//  power_ups.cpp
//  game2
//
//  Created by Portia Seater on 5/22/16.
//  Copyright © 2016 SDL_Squad. All rights reserved.
//

#include "items.hpp"
#include "main.hpp"
#include <math.h>


Items::Items(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int h, int w, Environment* passed_environment, int type) //Constructor
{
    environment = passed_environment;
    colliding = true;
    
    sdl_setup = passed_SDL_Setup;
    
    unit = new Sprite(sdl_setup->GetRenderer(), passed_image, starting_x, starting_y, w, h, CollisionRectangle(0,0,w,h));
    unit->SetOrigin((unit->GetWidth())/2, (unit->GetHeight())/2);
    
    prevX = starting_x;
    prevY = starting_y;
}


Items::~Items() //Destructor
{
    delete unit;
}

void Items::Draw()
{
    unit->Draw();
}

void Wall::Update()
{
    
}
