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
#include <vector>

class Environment;

class Door{
    public:
        int s;
        int e;
        Door(int start, int end){
            s = start;
            e = end;
        }
};

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
    void setAbove();
    void setBelow();
    bool isAbove();
    void addDoor(int start, int end);
    std::vector<Door*> doors;
    
protected:
    
    Environment* environment;
    SDL_Setup* sdl_setup;
    Sprite* unit;
    bool colliding;
    bool above;
    
    int prevX;
    int prevY;
    
    
    
};



#endif /* wall_hpp */
