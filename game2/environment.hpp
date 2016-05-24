#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "character.hpp"
#include "wall.hpp"
#include "NPC.hpp"
#include "items.hpp"
#include <vector>
#include "text.hpp"

class Character; //avoids error because Environment includes Character and vice versa
class Building;
class Main;

class Environment
{
public:
    Environment(SDL_Setup* passed_sdl_setup, Sprite* floor, Main* passed_main);
    ~Environment();
    
    void DrawBack();
    void Update();
    
    bool isSeen();
    bool isCollidingUp();
    bool isCollidingDown();
    
private:
    SDL_Setup* sdl_setup;
    Main* main;
    Sprite* floorSprite;
    SDL_Texture* wallSprite;
    
    int startTime;
    bool showMenu;
    SDL_Texture* characterImage;
    SDL_Texture* NPCBoyImage;
    SDL_Texture* NPCGirlImage;
    SDL_Texture* NPCPrincipalImage;
    SDL_Texture* wallImage;
    SDL_Texture* itemImage;
    bool wallCollidingUp;
    bool wallCollidingDown;
    Items* item;
    Character* character;
    std::vector<NPC*> npcList;
    std::vector<Wall*> horizontalWallList;
    std::vector<Wall*> verticalWallList;
    std::vector<Wall*> aboveWalls;
    std::vector<Wall*> belowWalls;
    int time;
    TextMessage* timesSeen;
    int seenInt;
    
    TextMessage* gameTime;
    
};

#endif // ENVIRONMENT_HPP
