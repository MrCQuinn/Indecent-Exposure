#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "collision_rectangle.hpp"
#include "character.hpp"
#include "wall.hpp"
#include "NPC.hpp"
#include <vector>

class Character; //avoids error because Environment includes Character and vice versa
class Building;
class AI;
class Main;

class Environment
{
public:
    Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, Main* passed_main);
    ~Environment();
    
    void DrawBack();
    void Update();
    
    bool isSeen();
    bool isCollidingUp();
    bool isCollidingDown();
    
private:
    SDL_Setup* sdl_setup;
    CollisionRectangle collision_rect;
    int *MouseX;
    int *MouseY;
    Main* main;
    int startTime;
    bool showMenu;
    SDL_Texture* characterImage;
    SDL_Texture* wallImage;
    bool wallCollidingUp;
    bool wallCollidingDown;

    Character* character;
    std::vector<NPC*> npcList;
    std::vector<Wall*> horizontalWallList;
    std::vector<Wall*> verticalWallList;
    std::vector<Wall*> aboveWalls;
    std::vector<Wall*> belowWalls;

    
};

#endif // ENVIRONMENT_HPP
