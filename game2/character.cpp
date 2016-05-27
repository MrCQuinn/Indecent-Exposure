#include "character.hpp"
#include "main.hpp"
#include <math.h>

Character::Character(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y,  Environment* passed_environment) //Constructor
{
    
    environment = passed_environment;
    //colliding = false;
    
    sdl_setup = passed_SDL_Setup;
    
    unit = new Sprite(sdl_setup->GetRenderer(), passed_image, starting_x, starting_y, 60, 90); //unit to move around
    unit->SetUpAnimation(4,4);
    unit->SetOrigin((unit->GetWidth())/2, (unit->GetHeight())/2);
    
    speed = 4;
    
    prevX = starting_x;
    prevY = starting_y;
    stopAnimation = false;
}

// For creating test character and not rendering
Character::Character(Environment *e) {
    unit = NULL;
    environment = e;
}

Character::~Character() //Destructor
{
    if (unit != NULL) {
        delete unit;
    }
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
    
    if(direction > 0){
        Move();    // Moves the character
    }
    
    
    
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
    int newX = unit->GetX();
    int newY = unit->GetY();
    
        if (direction == 1) //left
        {
            newX = unit->GetX() - speed;
        }
        if (direction == 2) //right
        {
            newX = unit->GetX() + speed;
        }
        if (direction == 3) //up
        {
            newY = unit->GetY() - speed;
        }
        if (direction == 4) //down
        {
            newY = unit->GetY() + speed;
        }
    
    
        if(environment->MoveAllowed(unit->GetX(), (unit->GetY()+(unit->GetHeight()/2)), newX, (newY+(unit->GetHeight()/2)))){
            unit->SetX(newX); // * 1.5f is speed
            unit->SetY(newY);
        }
    //std::cout << "new X: " << newX << "\n";
    //std::cout << "new Y: " << newY << "\n";
}

void Character::Animate(){
    
    if (!stopAnimation)
    {
        if (direction == 3) //Walking up
        {
            unit->Animation(0,3,0,100); //(start, end, selected animation, speed)
            
        } else if (direction == 1) //Walking Left
        {
            unit->Animation(0,3,1,100);
            
        } else if (direction == 4) //Walking Down
        {
            unit->Animation(0,3,2,100);
            
        } else //Walking Right
        {
            unit->Animation(0,3,3,100);
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

