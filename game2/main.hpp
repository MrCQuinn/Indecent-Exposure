#ifndef MAIN_HPP
#define MAIN_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include "environment.hpp"
#include "tests.hpp"
#include "items.hpp"

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
    void winGame();
    void endGame();
    
private:
    
    Character *unit;
    Environment* levelOne;
    Environment* levelTwo;
    Environment* levels[2];
    int level;
    int startTime;
    bool quit;
    bool start;
    bool pause;
    Sprite* splash;
    Sprite* floor;
    SDL_Setup* sdl_setup;
    
    SDL_Texture* wallImage1;
    SDL_Texture* wallImage2;
    SDL_Texture* wallImage3;
    SDL_Texture* wallImage4;
    SDL_Texture* wallImage5;
    
    SDL_Texture* wallImage6;
    SDL_Texture* wallImage7;
    SDL_Texture* wallImage8;
    SDL_Texture* doublelocker;
    SDL_Texture* locker;
    SDL_Texture* vertlocker;
    
    SDL_Texture* NPCBoyImage;
    SDL_Texture* NPCGirlImage;
    SDL_Texture* NPCPrincipalImage;
    SDL_Texture* NPCPrincipalImage2;
    
    SDL_Texture* characterImage;
    SDL_Texture* characterShoes;
    SDL_Texture* characterShirt;
    
    TextMessage* timesSeen;
    TextMessage* gameTime;
    
    SDL_Texture* item1Image;
    SDL_Texture* item2Image;
    SDL_Texture* item3Image;
};


#endif // MAIN_HPP
