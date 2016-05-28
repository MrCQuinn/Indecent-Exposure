#define _USE_MATH_DEFINES // So we can get value of pi from <cmath>

#include "environment.hpp"
#include "main.hpp"
#include "Point.hpp"
#include <algorithm>
#include <string>
#include <cmath>

Environment::Environment(SDL_Setup* passed_sdl_setup, Sprite* floor,  Main* passed_main, int i, int itemsC, SDL_Texture* characterImg)
{
    sdl_setup = passed_sdl_setup;
    main = passed_main;
    caughtCount = 0;
    itemsCollected = itemsC;
	// Zero out blockedPixels
	std::fill(&blockedPixels[0][0], &blockedPixels[0][0] + sizeof(blockedPixels), 0);
    floorSprite = floor;
    
    character = new Character(sdl_setup, characterImg, 90, 80, this);
    
    itemCount = i;
}

// Constructor for creating test environment without rendering:
Environment::Environment() {
    character = new Character(this);
    // Zero out blockedPixels
    std::fill(&blockedPixels[0][0], &blockedPixels[0][0] + sizeof(blockedPixels), 0);
}

Environment::~Environment()
{
    if (character != NULL) {
        delete character;
    }

    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        delete (*i);
    }
    
    for (std::vector<Wall*>::iterator i = wallList.begin(); i != wallList.end(); ++i)
    {
        delete (*i);
    }
    
    for (std::vector<Items*>::iterator i = itemList.begin(); i != itemList.end(); ++i)
    {
        delete (*i);
    }
    
    npcList.clear();
    wallList.clear();
    itemList.clear();
}

/*
 * All pixels in the rectangle formed by points (x1, y1) and (x2, y2)
 * are marked as "blocked", i.e. there's a wall there
 */
void Environment::addWall(int x1, int y1, int x2, int y2)
{
	for (int x = std::min(x1, x2); x<=std::max(x1, x2); ++x) {
		for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
			this->blockedPixels[y][x] = true;
		}
	}

}

void Environment::destroyWall(int x1, int y1, int x2, int y2)
{
    for (int x = std::min(x1, x2); x<=std::max(x1, x2); ++x) {
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y) {
            this->blockedPixels[y][x] = false;
        }
    }
    
}

/*
 * Returns true if there exists a line of sight between these two points
 * (i.e. no walls in the way)
 */
bool Environment::LineOfSightExists(int x1, int y1, int x2, int y2) {
    Point start = Point(x1, y1);
    Point end = Point(x2, y2);
    BresenhamPointIterator bpi = BresenhamPointIterator(&start, &end);
    for (Point curPixel = bpi.getNext();; curPixel = bpi.getNext()) {
        if (PixelIsBlocked(curPixel.x, curPixel.y)) {
            return false;
        }
        if (curPixel.x == x2 && curPixel.y == y2) {
            break;
        }
    }
    return true;
}

/*
 * Returns true if movement from cur position to new position is not blocked
 * (only for horizontal/vertical movement; no diagonal movement)
 *
 * This is intended for one frame of movement
 *
 * BUG: This will segfault if you give it values that are off the screen.
 * We should fix that. To do so, Environment needs to know how big it is
 */
bool Environment::MoveAllowed(int cur_x, int cur_y, int new_x, int new_y) {
	// If cur_x == new_x, we're moving vertically, else horizontally
	if (cur_x == new_x) {
		for (int y = std::min(cur_y, new_y); y <= std::max(cur_y, new_y); ++y) {
				if (this->blockedPixels[y][cur_x]) {
					// Pixel is blocked
					return false;
				}
		}
	} else {
		// moving horizontally
		for (int x = std::min(cur_x, new_x); x <= std::max(cur_x, new_x); ++x) {
			if (this->blockedPixels[cur_y][x]) {
				// Pixel is blocked
				return false;
			}
		}
	}
    return true;
}

void Environment::DrawBack()
{
    
    //draw floor
    floorSprite->Draw();
    
    //draw items
    for (std::vector<Items*>::iterator i = itemList.begin(); i != itemList.end(); ++i)
    {
        if(!(*i)->gotten()){
            (*i)->Draw();
        }
    }
    
    //draw character
    character->Draw();
    
    //draw NPC
    for (std::vector<NPC*>::iterator j = npcList.begin(); j != npcList.end(); ++j){
        (*j)->Draw();
    }
    
    //for all horizontal walls
    for (std::vector<Wall*>::iterator i = wallList.begin(); i != wallList.end(); ++i)
    {
        //draw wall
        (*i)->Draw();
        
        if((*i)->isAbove()){
            character->Draw();
        }
        
        // if npcs is in front of wall draw again
        for (std::vector<NPC*>::iterator j = npcList.begin(); j != npcList.end(); ++j)
        {
            if(((*i)->getWallY())+(.5 * (*i)->getWallH()) < ((*j)->getCharacterY()+((*j)->getCharacterH()*.5))){
                (*j)->Draw();
            }
        }
    }
    
    
    
}




// The way C/C++'s modulo operator works is dumb and wrong
static float realfmod(float num, float modulus) {
	return num >= 0 ? fmod(num, modulus) : modulus + fmod(num, modulus);
}

/*
 * Returns the angle towards (outside_x, outside_y) from (center_x, center_y)
 * like (center_x, center_y) is the center of a compass
 *
 * So North is 0 degrees, East is 90, etc.
 */
float Environment::GetAngle(int center_x, int center_y, int outside_x, int outside_y) {
	int delta_y = outside_y - center_y;
	int delta_x = outside_x - center_x;
	float angle = realfmod(atan2(delta_x, delta_y) * 180 / M_PI, 360);

	return angle;
}

/*
 * Runs every frame and updates the state of the game
 * determines the order to draw level parts
 *
 *  Updates Character and all NPCs
 */

void Environment::Update()
{
    //update character
    character->Update();
    
    //Update walls to position relative to character
    for (std::vector<Wall*>::iterator i = wallList.begin(); i != wallList.end(); ++i)
    {
        if((((*i)->getWallY())+(.5 * (*i)->getWallH()) < (character->getCharacterY()+(character->getCharacterH()*.5)))){
            (*i)->setAbove();
        }else{
            (*i)->setBelow();
        }
    }
    
    //Update all NPCs
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        (*i)->Update();
    }
    
    //check for item pickup
    for (std::vector<Items*>::iterator i = itemList.begin(); i != itemList.end(); ++i)
    {
        if(!(*i)->gotten()){
            if(character->getCharacterX() > ((*i)->getItemX() - ((*i)->getItemW()/2)) && character->getCharacterX() < ((*i)->getItemX() + ((*i)->getItemW()/2))){
                if(character->getCharacterY() > ((*i)->getItemY() - ((*i)->getItemH()/2)) && character->getCharacterY() < ((*i)->getItemY() + ((*i)->getItemH()/2))){
                    (*i)->pickup();
                    itemsCollected++;
                    if(itemsCollected == 1){
                        character->gainShoes();
                    }else if(itemsCollected == 2){
                        character->gainShirt();
                    }
                    if(itemsCollected == itemCount){
                        destroyWall(980, 645, 1080, 715);
                    }
                }
            }
        }
    }
    
}

/*
 * Returns true if pixel is marked as blocked (i.e. is inside a wall)
 */
bool Environment::PixelIsBlocked(int x, int y) {
	return this->blockedPixels[y][x];
}

// Iterates through all NPCs, checking if they can see the player
bool Environment::isSeen(){
    //for all npc's
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        if ((*i)->canSeePlayer()) {
            caughtCount++;
            return true;
        }
    }
    return false;
}

bool Environment::isComplete(){
    if(character->getCharacterX() > 980){
        return true;
    }
    return false;
}

int Environment::timesSeen(){
    return caughtCount;
}

void Environment::addWallpaper(Wall* wall){
    wallList.push_back(wall);
}

void Environment::addNPC(NPC* npc){
    npcList.push_back(npc);
}
void Environment::addItem(Items* item){
    itemList.push_back(item);
}

Character * Environment::getCharPointer()
{
    return this->character;
}

std::vector<NPC*>* Environment::getNPCVector()
{
    return &(this->npcList);
}

