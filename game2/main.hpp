#ifndef MAIN_HPP
#define MAIN_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "environment.hpp"

class Environment;
class AI;

class Main
{
public:
    Main();
    ~Main();
    
    void GameLoop();
    double GetDistance(int x1, int y1, int x2, int y2);
    void endGame(int loser);
    
private:
    
    Character *unit;
    Environment* gameMap;
    bool quit;
    bool start;
    bool quitEarly;
    Sprite* splash;
    Sprite* floor;
    SDL_Setup* sdl_setup;
};


#endif // MAIN_HPP
