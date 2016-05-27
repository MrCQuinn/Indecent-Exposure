#define _USE_MATH_DEFINES // So we can get value of pi from <cmath>

#include "environment.hpp"
#include "main.hpp"
#include "Point.hpp"
#include <algorithm>
#include <string>
#include <cmath>

Environment::Environment(SDL_Setup* passed_sdl_setup, Sprite* floor,  Main* passed_main)
{
    sdl_setup = passed_sdl_setup;
    main = passed_main;
    caughtCount = 0;
	// Zero out blockedPixels
	std::fill(&blockedPixels[0][0], &blockedPixels[0][0] + sizeof(blockedPixels), 0);
    floorSprite = floor;
    
    characterImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/character_big.png");
    character = new Character(sdl_setup, characterImage, 90, 80, this);
    
    //Create item image
    itemImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/item.png");
    item = new Items(sdl_setup, itemImage, 975, 610, 32, 32, this);
}

// Constructor for creating test environment without rendering:
Environment::Environment() {
    character = new Character(this);
}

Environment::~Environment()
{
    delete character;
    delete item;
    //delete timesSeen;
    //delete gameTime;
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        delete (*i);
    }
    
    for (std::vector<Wall*>::iterator i = wallList.begin(); i != wallList.end(); ++i)
    {
        delete (*i);
    }
    npcList.clear();
    wallList.clear();
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
    
    //draw everyone
    floorSprite->Draw();
    character->Draw();
    
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
    
    item->Draw();
    
}

int Environment::timesSeen(){
    return caughtCount;
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
    character->Update();
    
    for (std::vector<Wall*>::iterator i = wallList.begin(); i != wallList.end(); ++i)
    {
        if((((*i)->getWallY())+(.5 * (*i)->getWallH()) < (character->getCharacterY()+(character->getCharacterH()*.5)))){
            (*i)->setAbove();
        }else{
            (*i)->setBelow();
        }
    }
    
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        (*i)->Update();
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

bool Environment::backLevel(){
    if(character->getCharacterX() < 0){
        return true;
    }
    return false;
}

void Environment::addWallpaper(Wall* wall){
    wallList.push_back(wall);
}

void Environment::addNPC(NPC* npc){
    npcList.push_back(npc);
}

