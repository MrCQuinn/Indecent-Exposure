#include "NPC.hpp"
#include "main.hpp"
#include "Point.hpp"
#include <math.h>

NPC::NPC(SDL_Setup* passed_SDL_Setup, SDL_Texture* passed_image, int starting_x, int starting_y, Environment* passed_environment, int type, int dist) //Constructor
{
    
    environment = passed_environment;
    colliding = false;
    
    sdl_setup = passed_SDL_Setup;
    
    unit = new Sprite(sdl_setup->GetRenderer(), passed_image, starting_x, starting_y, 60, 80); //unit to move around
    unit->SetUpAnimation(4,4);
    unit->SetOrigin((unit->GetWidth())/2, (unit->GetHeight())/2);
    
    prevX = starting_x;
    prevY = starting_y;
    stopAnimation = false;
    
    npcType = type;
    npcDist = dist;
    
    speed = 3;
    
    
    if(type== 1){
        direction = 1;
    }else if(type == 2){
        direction = 1;
    }else if(type == 3){
        direction = 3;
    }
    
}

NPC::~NPC() //Destructor
{
    delete unit;
}

double NPC::GetDistance(int x1, int y1, int x2, int y2)
{ //used for unit to take most direct path to target
    double differenceX = x1 - x2;
    double differenceY = y1 - y2;
    double distance = sqrt((differenceX * differenceX) + (differenceY * differenceY));
    return distance;
}

void NPC::Draw()
{
    unit->Draw();
}

void NPC::Update()
{
    Animate();
    Move();    // Moves the character
    
    
    //direction
    // 1 = left; 2 = right; 3 = up; 4 = down
    
    if(npcType == 1){//back and forth
        if(direction == 1){
            if(unit->GetX()<(prevX-npcDist)){
                prevX = unit->GetX();
                direction = 2;
            }
        }else if(direction == 2){
            if(unit->GetX()>(prevX+npcDist)){
                prevX = unit->GetX();
                direction = 1;
            }
        }
    }else if(npcType == 2){//circle
        if(direction == 1){
            if(unit->GetX()<(prevX-npcDist)){
                prevX = unit->GetX();
                direction = 4;
            }
        }else if(direction == 2){
            if(unit->GetX()>(prevX+npcDist)){
                prevX = unit->GetX();
                direction = 3;
            }
        }else if(direction == 4){
            if(unit->GetY()>(prevY+npcDist)){
                prevY = unit->GetY();
                direction = 2;
            }
        }else if(direction == 3){
            if(unit->GetY()<(prevY-npcDist)){
                prevY = unit->GetY();
                direction = 1;
            }
        }
    }else if(npcType == 3){//up and down
        if(direction == 3){
            if(unit->GetY()<(prevY-npcDist)){
                prevY = unit->GetY();
                direction = 4;
            }
        }else if(direction == 4){
            if(unit->GetY()>(prevY+npcDist)){
                prevY = unit->GetY();
                direction = 3;
            }
        }
    }
}

void NPC::Move(){
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
    
    unit->SetX(newX);
    unit->SetY(newY);

}

void NPC::Animate(){
    
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


int NPC::getCharacterX(){
    return unit->GetX();
}

int NPC::getCharacterY(){
    return unit->GetY();
}

int NPC::getCharacterW(){
    return unit->GetWidth();
}

int NPC::getCharacterH(){
    return unit->GetHeight();
}

void NPC::setDirection(int d)
{
    direction = d;
    if(direction >  0){
        moving = true;
    }
}

/*
 *  Direction numbers:
 *       3
 *      /|\
 *  1 <--+--> 2
 *      \|/
 *       4
 */
int NPC::getNPCDirection(){
    return direction;
}

bool NPC::canSeePlayer()
{
    int player_x = environment->character->getCharacterX();
    int player_y = environment->character->getCharacterY();
    int our_x = this->getCharacterX();
    int our_y = this->getCharacterY();
    int delta_x = player_x - our_x;
    int delta_y = player_y - our_y;
    // Find what octant the player is in relative to the NPC:
    int octant = BresenhamPointIterator::get_octant(delta_x, delta_y);

    // Only bother checking line of sight if the NPC if facing player:
    bool facingPlayer = false;
    int NPCDirection = this->getNPCDirection();
    if (NPCDirection == 2) {
        // NPC facing right
        if (octant == 0 || octant == 7) {
            facingPlayer = true;
        }
    } else if (NPCDirection == 3) {
        // NPC facing up: Note that y decreases going up, so this is backwards from what you would expect
        if (octant == 5 || octant == 6) {
            facingPlayer = true;
        }
    } else if (NPCDirection == 1) {
        // NPC facing left
        if (octant == 3 || octant == 4) {
            facingPlayer = true;
        }
    } else {
        // NPC facing down: Note that y increases going down, so this is backwards from what you would expect
        if (octant == 1 || octant == 2) {
            facingPlayer = true;
        }
    }

    if (facingPlayer) {
        return environment->LineOfSightExists(our_x, our_y, player_x, player_y);
    }
    return false;
}

