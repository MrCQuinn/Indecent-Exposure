#ifndef NPC_HPP
#define NPC_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include <math.h>

class Environment;

class NPC
{
public:
    NPC(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, Environment* passed_environment, int type, int dist);
    NPC() {}
    ~NPC();
    
    
    double GetDistance(int x1, int y1, int x2, int y2);
    virtual void Update();
    void Draw();
    Sprite* GetCharacter() { return unit; }
    void Animate();
    void Select();
    void Move();
    virtual void setDirection(int d);
    int getCharacterX();
    int getCharacterY();
    int getCharacterW();
    int getCharacterH();
    int getNPCDirection();
    
protected:
    
    Environment* environment;
    SDL_Setup* sdl_setup;
    Sprite* unit;
    bool colliding;
    
    int prevX;
    int prevY;
    bool stopAnimation;
    int direction;
    bool moving;
    int npcType;
    int npcDist;
    
};


#endif // NPC_HPP_INCLUDED
