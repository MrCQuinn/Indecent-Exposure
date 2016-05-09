#include "environment.hpp"
#include "main.hpp"

Environment::Environment(SDL_Setup* passed_sdl_setup, int *passed_MouseX, int *passed_MouseY, Main* passed_main)
{
    sdl_setup = passed_sdl_setup;
    MouseX = passed_MouseX;
    MouseY = passed_MouseY;
    main = passed_main;
    startTime = SDL_GetTicks()/1000; //ensures game time corresponds to when spacebar hit on splash screen and game begins
    
    characterImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/character.png");
    character = new Character(sdl_setup, characterImage, 300, 200, MouseX, MouseY, this);
    
    //create NPC image
//    npc = new NPC(sdl_setup, characterImage, 300, 400, MouseX, MouseY, this, 1, 200);
//    npc2 = new NPC(sdl_setup, characterImage, 500, 400, MouseX, MouseY, this, 2, 200);
    
    npcList.push_back(new NPC(sdl_setup, characterImage, 300, 400, MouseX, MouseY, this, 1, 200));
    npcList.push_back(new NPC(sdl_setup, characterImage, 500, 400, MouseX, MouseY, this, 2, 200));

    
    
}

Environment::~Environment()
{
    delete character;
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        delete (*i);
    }
}

void Environment::DrawBack()
{
    character->Draw();
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        (*i)->Draw();
    }
}

void Environment::Update()
{
    
    character->Update();
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        (*i)->Update();
    }
}

bool Environment::isSeen(){
    //for all npc's
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        if((*i)->getNPCDirection() < 3){
        if((character->getCharacterY() > ((*i)->getCharacterY() - (*i)->getCharacterH())) && (character->getCharacterY() < ((*i)->getCharacterY() + (*i)->getCharacterH()))){
            if((*i)->getNPCDirection() == 1){
                if(character->getCharacterX() > ((*i)->getCharacterX() - (*i)->getCharacterW() - 40) && character->getCharacterX() < (*i)->getCharacterX()){
                    std::cout << "seen to left character x = " << character->getCharacterX() << " and npc x = " << (*i)->getCharacterX() << std::endl;
                    return true;
                }
            }else if((*i)->getNPCDirection()== 2){
                if(character->getCharacterX() < ((*i)->getCharacterX() + (*i)->getCharacterW() + 40) && character->getCharacterX() > (*i)->getCharacterX()){
                    std::cout << "seen to right character x = " << character->getCharacterX() << " and npc x = " << (*i)->getCharacterX() << std::endl;
                    return true;
                }
            }
        }
    }else{
        if((character->getCharacterX() > ((*i)->getCharacterX() - (*i)->getCharacterW())) && (character->getCharacterX() < ((*i)->getCharacterX() + (*i)->getCharacterW()))){
            if((*i)->getNPCDirection() == 3){
                if(character->getCharacterY() > ((*i)->getCharacterY() - 40) && character->getCharacterY() < (*i)->getCharacterY()){
                    std::cout << "seen above" << std::endl;
                    return true;
                }
            }else if((*i)->getNPCDirection()== 4){
                if(character->getCharacterY() < ((*i)->getCharacterX() + 40) && character->getCharacterY() > (*i)->getCharacterY()){
                    std::cout << "seen below" << std::endl;
                    return true;
                }
            }
        }
    }
    }
    
    return false;
}


//void Environment::setCollisionImage(Sprite* building)
//{
//    building->setCollisionImage(collisionImage20);
//}

//void Environment::endGame(int loser) //tells Main game is over and declares winner
//{
//    main->endGame(loser);
//}
