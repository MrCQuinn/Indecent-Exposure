//
//  power_ups.hpp
//  game2
//
//  Created by Portia Seater on 5/22/16.
//  Copyright © 2016 SDL_Squad. All rights reserved.
//

#ifndef power_ups_hpp
#define power_ups_hpp

#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include <math.h>
#include <vector>

class Environment;

class Items
{
public:
    Items(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int h, int w, Environment* passed_environment, int type);
    Items() {}
    ~Items();
    
    void Draw();
    
protected:
    
    Environment* environment;
    SDL_Setup* sdl_setup;
    Sprite* unit;
    bool colliding;
    
    int prevX;
    int prevY;
    
    
    
};

#endif /* power_ups_hpp */
