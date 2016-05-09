#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include <math.h>

class Environment; //avoids error because Environment includes Character and vice versa
class Building;

class Character
{
public:
    Character(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, int *passed_MouseX, int *passed_MouseY, Environment* passed_environment);
    Character() {}
    ~Character();
    

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
    
protected:
    
    Environment* environment;
    int *MouseX;
    int *MouseY;
    SDL_Setup* sdl_setup;
    Sprite* unit;
    bool colliding;
    
    int prevX;
    int prevY;
    bool stopAnimation;
    int direction;
    bool moving;
    
};


#endif // CHARACTER_HPP_INCLUDED
