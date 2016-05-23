//
//  wall.cpp
//  game2
//
//  Created by Charlie Quinn on 5/11/16.
//  Copyright © 2016 SDL_Squad. All rights reserved.
//

#include "wall.hpp"
#include <math.h>

Wall::Wall(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int h, int w, Environment* passed_environment) //Constructor
{
    
    environment = passed_environment;
    colliding = false;
    
    sdl_setup = passed_SDL_Setup;
    
    unit = new Sprite(sdl_setup->GetRenderer(), passed_image, starting_x, starting_y, w, h);
    unit->SetOrigin((unit->GetWidth())/2, (unit->GetHeight())/2);
    
    prevX = starting_x;
    prevY = starting_y;
}

Wall::~Wall() //Destructor
{
    delete unit;
}

void Wall::Draw()
{
    unit->Draw();
}

void Wall::Update()
{
    
}

void Wall::addDoor(int start, int end){
    doors.push_back(new Door(start, end));
}

int Wall::getWallX(){
    return unit->GetX();
}

int Wall::getWallY(){
    return unit->GetY();
}

int Wall::getWallW(){
    return unit->GetWidth();
}

int Wall::getWallH(){
    return unit->GetHeight();
}
