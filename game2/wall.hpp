//
//  wall.hpp
//  Indecent-Exposure
//
//  Created by Charlie Quinn on 5/11/16.
//  Copyright © 2016 SDL_Squad. All rights reserved.
//

#ifndef WALL_HPP
#define WALL_HPP

#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include <math.h>

class Environment;

class Wall
{
public:
    Wall(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int h, int w, Environment* passed_environment);
    Wall() {}
    ~Wall();
    
    
    double GetDistance(int x1, int y1, int x2, int y2);
    virtual void Update();
    void Draw();
    int getWallX();
    int getWallY();
    int getWallW();
    int getWallH();
    
protected:
    
    Environment* environment;
    SDL_Setup* sdl_setup;
    Sprite* unit;
    bool colliding;
    
    int prevX;
    int prevY;
    
};

#endif /* wall_hpp */
