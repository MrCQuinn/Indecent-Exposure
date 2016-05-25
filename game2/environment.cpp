#define _USE_MATH_DEFINES // So we can get value of pi from <cmath>

#include "environment.hpp"
#include "main.hpp"
#include <algorithm>
#include <string>
#include <cmath>

Environment::Environment(SDL_Setup* passed_sdl_setup, Sprite* floor,  Main* passed_main)
{
    sdl_setup = passed_sdl_setup;
    main = passed_main;
    startTime = SDL_GetTicks()/1000; //ensures game time corresponds to when spacebar hit on splash screen and game begins
	// Zero out blockedPixels
	std::fill(&blockedPixels[0][0], &blockedPixels[0][0] + sizeof(blockedPixels), 0);

    

    floorSprite = floor;
    
    characterImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/character_big.png");
    character = new Character(sdl_setup, characterImage, 100, 150, this);
    
    wallImage1 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/first_piece.png");
    wallImage2 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/second_piece.png");
    wallImage3 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/third_piece.png");
    wallImage4 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/fourth_piece.png");
    wallImage5 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/fifth_piece.png");
    

    wallList.push_back(new Wall(sdl_setup, wallImage1, 512, 45, 90, 1024, this));
    wallList.push_back(new Wall(sdl_setup, wallImage2, 512, 190, 200, 1024, this));
    wallList.push_back(new Wall(sdl_setup, wallImage3, 512, 377, 174, 1024, this));
    wallList.push_back(new Wall(sdl_setup, wallImage4, 512, 531, 134, 1024, this));
    wallList.push_back(new Wall(sdl_setup, wallImage5, 512, 685, 176, 1024, this));
    
    addWall(0, 0, 1024, 90);
    
    timesSeen = new TextMessage(sdl_setup->GetRenderer(), "Times Seen: " + std::to_string(seenInt), 782, 20);
    seenInt = 0;
    
    gameTime = new TextMessage(sdl_setup->GetRenderer(), "Total Game Time: " + std::to_string(startTime), 750, 2);

    wallCollidingUp = false;
    wallCollidingDown = false;

    //create NPC images here
    NPCBoyImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/b_student_big.png");
    NPCGirlImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/g_student_sprite.png");
    NPCPrincipalImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/principal_sprite.png");

    //Create item image
    itemImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/item.png");
    item = new Items(sdl_setup, itemImage, 975, 610, 32, 32, this);
    
    npcList.push_back(new NPC(sdl_setup, NPCBoyImage, 300, 400, this, 1, 200));
    npcList.push_back(new NPC(sdl_setup, NPCBoyImage, 500, 400, this, 2, 200));
    npcList.push_back(new NPC(sdl_setup, NPCGirlImage, 700, 200, this, 2, 200));
    npcList.push_back(new NPC(sdl_setup, NPCPrincipalImage, 700, 420, this, 3, 400));

    //add doors
//    int index = 0;
//    for (std::vector<Wall*>::iterator i = wallList.begin(); i != wallList.end(); ++i)
//    {
//        if(index == 1){
//            (*i)->addDoor(820,980);
//        }
//        index++;
//    }

    // TODO: Add doors
    
    
}

Environment::~Environment()
{
    delete character;
    delete item;
    delete timesSeen;
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
 * Returns true if movement from cur position to new position is not blocked
 * (only for horizontal/vertical movement; no diagonal movement)
 *
 * This is intended for one frame of movement
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
    time = (SDL_GetTicks() - startTime)/1000;
    timesSeen->Draw("Times Seen: " + std::to_string((int)seenInt));
    gameTime->Draw("Total Game Time: " + std::to_string(time));
    
    item->Draw();
    
}


// The way C/C++'s modulo operator works is dumb and wrong
static float realfmod(float num, float modulus) {
	return num >= 0 ? fmod(num, modulus) : modulus + fmod(num, modulus);
}

/*
 * Returns the angle towards (outside_x, outside_y) from (center_x, center_y)
 * as if (center_x, center_y) is the middle of a compass
 */
static float GetAngle(int center_x, int center_y, int outside_x, int outside_y) {
	int delta_y = outside_y - center_y;
	int delta_x = outside_x - center_x;
	float angle = realfmod(atan2(delta_x, delta_y) * 180 / M_PI, 360);

	return angle; // FIXME return angle relative to North
}

void Environment::Update()
{
    character->Update();
    
    wallCollidingDown = false;
    wallCollidingUp = false;
    
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

	// TODO add collision detection
}

/*
 * Returns true if pixel is marked as blocked (i.e. is inside a wall)
 */
bool Environment::PixelIsBlocked(int x, int y) {
	return this->blockedPixels[y][x];
}

bool Environment::isSeen(){
    //for all npc's
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        if((*i)->getNPCDirection() < 3){
        if((character->getCharacterY() > ((*i)->getCharacterY() - (*i)->getCharacterH())) && (character->getCharacterY() < ((*i)->getCharacterY() + (*i)->getCharacterH()))){
            if((*i)->getNPCDirection() == 1){
                if(character->getCharacterX() > ((*i)->getCharacterX() - (*i)->getCharacterW() - 40) && character->getCharacterX() < (*i)->getCharacterX()){
                    //std::cout << "seen to left character x = " << character->getCharacterX() << " and npc x = " << (*i)->getCharacterX() << std::endl;
                    seenInt++;
                    return true;
                }
            }else if((*i)->getNPCDirection()== 2){
                if(character->getCharacterX() < ((*i)->getCharacterX() + (*i)->getCharacterW() + 40) && character->getCharacterX() > (*i)->getCharacterX()){
                    //std::cout << "seen to right character x = " << character->getCharacterX() << " and npc x = " << (*i)->getCharacterX() << std::endl;
                    seenInt++;
                    return true;
                }
            }
        }
    }else{
        if((character->getCharacterX() > ((*i)->getCharacterX() - (*i)->getCharacterW())) && (character->getCharacterX() < ((*i)->getCharacterX() + (*i)->getCharacterW()))){
            if((*i)->getNPCDirection() == 3){
                if(character->getCharacterY() > ((*i)->getCharacterY() - 40) && character->getCharacterY() < (*i)->getCharacterY()){
                    //std::cout << "seen above" << std::endl;
                    seenInt++;
                    return true;
                }
            }else if((*i)->getNPCDirection()== 4){
                if(character->getCharacterY() < ((*i)->getCharacterX() + 40) && character->getCharacterY() > (*i)->getCharacterY()){
                    //std::cout << "seen below" << std::endl;
                    seenInt++;
                    return true;
                }
            }
        }
    }
    }
    
    return false;
}

bool Environment::isCollidingUp(){
    return wallCollidingUp;
}

bool Environment::isCollidingDown(){
    return wallCollidingDown;
}
