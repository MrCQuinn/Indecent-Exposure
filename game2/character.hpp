#ifndef CHARACTER_HPP
#define CHARACTER_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "sprite.hpp"
#include <math.h>

class Environment; //avoids error because Environment includes Character and vice versa

class Character
{
public:
    Character(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, Environment* passed_environment);
    Character() {}
    Character(Environment * e);
    ~Character();
    
    virtual void Update();
    void Draw();
    Sprite* GetCharacter() { return unit; }
    void Animate();
    void Move();
    virtual void setDirection(int d);
    int getCharacterX();
    int getCharacterY();
    int getCharacterW();
    int getCharacterH();
    void gainShoes();
    void gainShirt();
    
protected:
    
    Environment* environment;
    SDL_Setup* sdl_setup;
    Sprite* unit;
    bool collidingUp;
    
    int prevX;
    int prevY;
    bool stopAnimation;
    int direction;
    bool moving;
    
    int speed;
    
    bool isSeen();
    
    SDL_Texture* shoes;
    SDL_Texture* shirt;
    
};


#endif // CHARACTER_HPP_INCLUDED
