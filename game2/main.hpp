#ifndef MAIN_HPP
#define MAIN_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "environment.hpp"
#include "tests.hpp"

class Environment;
class AI;

class Main
{
public:
    Main();
    ~Main();

    void runTests();
    
    void GameLoop();
    double GetDistance(int x1, int y1, int x2, int y2);
    void endGame(int loser);
    
private:
    
    Character *unit;
    Environment* levelOne;
    int level;
    bool quit;
    bool start;
    bool quitEarly;
    Sprite* splash;
    Sprite* floor;
    SDL_Setup* sdl_setup;
    
    SDL_Texture* wallImage1;
    SDL_Texture* wallImage2;
    SDL_Texture* wallImage3;
    SDL_Texture* wallImage4;
    SDL_Texture* wallImage5;
    
    SDL_Texture* NPCBoyImage;
    SDL_Texture* NPCGirlImage;
    SDL_Texture* NPCPrincipalImage;
};


#endif // MAIN_HPP
