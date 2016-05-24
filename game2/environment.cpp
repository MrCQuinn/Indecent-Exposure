#include "environment.hpp"
#include "main.hpp"
#include <algorithm>
#include <string>

Environment::Environment(SDL_Setup* passed_sdl_setup, Sprite* floor,  Main* passed_main)
{
    sdl_setup = passed_sdl_setup;
    main = passed_main;
    startTime = SDL_GetTicks()/1000; //ensures game time corresponds to when spacebar hit on splash screen and game begins
    
    floorSprite = floor;
    
    characterImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/character.png");
    character = new Character(sdl_setup, characterImage, 100, 150, this);
    
    wallImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/horWall.png");
    
    horizontalWallList.push_back(new Wall(sdl_setup, wallImage, 512, 100, 100, 1024, this));
    horizontalWallList.push_back(new Wall(sdl_setup, wallImage, 512, 300, 100, 1024, this));
    horizontalWallList.push_back(new Wall(sdl_setup, wallImage, 512, 500, 100, 1024, this));
    horizontalWallList.push_back(new Wall(sdl_setup, wallImage, 512, 700, 100, 1024, this));
    horizontalWallList.push_back(new Wall(sdl_setup, wallImage, 512, 900, 100, 1024, this));
 
    wallImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/verWall.png");
    //verticalWallList.push_back(new Wall(sdl_setup, wallImage, 600, 400, 700, 100, this));
    
    timesSeen = new TextMessage(sdl_setup->GetRenderer(), "Times Seen: " + std::to_string(seenInt), 150, 0);
    seenInt = 0;

    wallCollidingUp = false;
    wallCollidingDown = false;

    //create NPC images here
    NPCBoyImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/b_student_big.png");
    NPCGirlImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/g_student_sprite.png");
    NPCPrincipalImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/principal_sprite.png");

    //Create item image
    itemImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/item.png");
    item = new Items(sdl_setup, itemImage, 110, 510, 32, 32, this);
    
    npcList.push_back(new NPC(sdl_setup, NPCBoyImage, 300, 400, this, 1, 200));
    npcList.push_back(new NPC(sdl_setup, NPCBoyImage, 500, 400, this, 2, 200));
    npcList.push_back(new NPC(sdl_setup, NPCGirlImage, 700, 200, this, 2, 200));
    npcList.push_back(new NPC(sdl_setup, NPCPrincipalImage, 700, 420, this, 3, 400));
    
    
    //add doors
    for (std::vector<Wall*>::iterator i = horizontalWallList.begin(); i != horizontalWallList.end(); ++i)
    {
        (*i)->addDoor(650,750);
    }
    
    
}

Environment::~Environment()
{
    delete character;
    delete item;
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        delete (*i);
    }
    for (std::vector<Wall*>::iterator i = horizontalWallList.begin(); i != horizontalWallList.end(); ++i)
    {
        delete (*i);
    }
    for (std::vector<Wall*>::iterator i = verticalWallList.begin(); i != verticalWallList.end(); ++i)
    {
        delete (*i);
    }
    for (std::vector<Wall*>::iterator i = aboveWalls.begin(); i != aboveWalls.end(); ++i)
    {
        delete (*i);
    }
    for (std::vector<Wall*>::iterator i = belowWalls.begin(); i != belowWalls.end(); ++i)
    {
        delete (*i);
    }
}

void Environment::DrawBack()
{
    
    //draw everyone
    floorSprite->Draw();
    character->Draw();
    item->Draw();
    
    //for all vertical walls
    for (std::vector<Wall*>::iterator i = verticalWallList.begin(); i != verticalWallList.end(); ++i)
    {
        //draw wall
        (*i)->Draw();
    }
    
    for (std::vector<NPC*>::iterator j = npcList.begin(); j != npcList.end(); ++j){
        (*j)->Draw();
    }
    
    
    
    //for all horizontal walls
    for (std::vector<Wall*>::iterator i = horizontalWallList.begin(); i != horizontalWallList.end(); ++i)
    {
        //draw wall
        (*i)->Draw();
        
        // if character is in front of wall draw again
        if((((*i)->getWallY())+(.5 * (*i)->getWallH()) < (character->getCharacterY()+(character->getCharacterH()*.5)))){
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

void Environment::Update()
{
    character->Update();
    
    wallCollidingDown = false;
    wallCollidingUp = false;
    
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        (*i)->Update();
    }
    for (std::vector<Wall*>::iterator i = horizontalWallList.begin(); i != horizontalWallList.end(); ++i)
    {
        if(character->getCharacterY()> (*i)->getWallY()){//character is above wall
            aboveWalls.push_back((*i));
            belowWalls.erase(std::remove(belowWalls.begin(), belowWalls.end(), (*i)), belowWalls.end());
            //remove from belowWalls
        }else if(character->getCharacterY() < (*i)->getWallY()){
            belowWalls.push_back((*i));
            aboveWalls.erase(std::remove(aboveWalls.begin(), aboveWalls.end(), (*i)), aboveWalls.end());
        }
    }
    for (std::vector<Wall*>::iterator i = aboveWalls.begin(); i != aboveWalls.end(); ++i)
    {
        if(character->getCharacterY() < ((*i)->getWallY() + 10)){//character is below wall
            wallCollidingUp = true;
            for (std::vector<Door*>::iterator j = (*i)->doors.begin(); j != (*i)->doors.end(); ++j)
            {
                if(character->getCharacterX() > (*j)->s && character->getCharacterX() < (*j)->e){
                    wallCollidingUp = false;
                }
            }
        }
    }
    for (std::vector<Wall*>::iterator i = belowWalls.begin(); i != belowWalls.end(); ++i)
    {
        if(character->getCharacterY() > ((*i)->getWallY() - 10)){//character is above wall
            wallCollidingDown = true;
            for (std::vector<Door*>::iterator j = (*i)->doors.begin(); j != (*i)->doors.end(); ++j)
            {
                if(character->getCharacterX() > (*j)->s && character->getCharacterX() < (*j)->e){
                    wallCollidingDown = false;
                }
            }
        }
    }
    
    timesSeen->Draw("Times Seen: " + std::to_string((int)seenInt));
    
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
