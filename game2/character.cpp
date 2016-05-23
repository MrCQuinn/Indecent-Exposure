#include "character.hpp"
#include "main.hpp"
#include <math.h>

Character::Character(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y,  Environment* passed_environment) //Constructor
{
    
    environment = passed_environment;
    //colliding = false;
    
    sdl_setup = passed_SDL_Setup;
    
    unit = new Sprite(sdl_setup->GetRenderer(), passed_image, starting_x, starting_y, 60, 90); //unit to move around
    unit->SetUpAnimation(2,4);
    unit->SetOrigin((unit->GetWidth())/2, (unit->GetHeight())/2);
    
    prevX = starting_x;
    prevY = starting_y;
    stopAnimation = false;
}

Character::~Character() //Destructor
{
    delete unit;
}

double Character::GetDistance(int x1, int y1, int x2, int y2)
{ //used for unit to take most direct path to target
    double differenceX = x1 - x2;
    double differenceY = y1 - y2;
    double distance = sqrt((differenceX * differenceX) + (differenceY * differenceY));
    return distance;
}

void Character::Draw()
{
    unit->Draw();
}

void Character::Update()
{
    if(isSeen()){
        unit->SetY(prevY);
        unit->SetX(prevX);
    }
    
    //collidingUp = environment->isCollidingUp(unit->GetY());
    
    Animate();
    Move();    // Moves the character
    
    
    if(sdl_setup->GetEv()->type == SDL_KEYDOWN){
        if(sdl_setup->GetEv()->key.keysym.sym == SDLK_DOWN){
            //MOVE CHARACTER DOWN
            direction = 4;
            stopAnimation = false;
        }else if(sdl_setup->GetEv()->key.keysym.sym == SDLK_UP){
            //MOVE CHARACTER UP
            direction = 3;
            stopAnimation = false;
        }else if(sdl_setup->GetEv()->key.keysym.sym == SDLK_LEFT){
            //MOVE CHARACTER LEFT
            direction = 1;
            stopAnimation = false;
        }else if(sdl_setup->GetEv()->key.keysym.sym == SDLK_RIGHT){
            //MOVE CHARACTER RIGHT
            direction = 2;
            stopAnimation = false;
        }
    }else{
        direction = 0;
        stopAnimation = true;
    }
}

bool Character::isSeen(){
    if(environment->isSeen()){
        return true;
    }else{
        return false;
    }
}

void Character::Move(){
   // if (!colliding){
        if (direction == 1) //left
        {
            unit->SetX(unit->GetX() - (.5 * 1.5f )); // * 1.5f is speed
        }
        if (direction == 2) //right
        {
            unit->SetX(unit->GetX() + (.5 * 1.5f ));
        }
        if (direction == 3) //up
        {
            if(!environment->isCollidingUp()){
                unit->SetY(unit->GetY() - (.5 * 1.5f ));
            }
        }
        if (direction == 4) //down
        {
            if(!environment->isCollidingDown()){
                unit->SetY(unit->GetY() + (.5 * 1.5f ));
            }
        }
    //}
    if(unit->GetX()>1024){
        unit->SetX(0);
    }
    if(unit->GetX()<0){
        unit->SetX(1024);
    }
    if(unit->GetY()>768){
        unit->SetY(0);
    }
    if(unit->GetY()<0){
        unit->SetY(768);
    }
}

void Character::Animate(){
    
    if (!stopAnimation)
    {
        if (direction == 3) //Walking up
        {
            unit->Animation(0,1,0,100); //(start, end, selected animation, speed)
            
        } else if (direction == 1) //Walking Left
        {
            unit->Animation(0,1,1,100);
            
        } else if (direction == 4) //Walking Down
        {
            unit->Animation(0,1,2,100);
            
        } else //Walking Right
        {
            unit->Animation(0,1,3,100);
        }
    }
}


int Character::getCharacterX(){
    return unit->GetX();
}

int Character::getCharacterY(){
    return unit->GetY();
}

int Character::getCharacterW(){
    return unit->GetWidth();
}

int Character::getCharacterH(){
    return unit->GetHeight();
}

void Character::setDirection(int d)
{
    direction = d;
    if(direction >  0){
        moving = true;
    }
}

