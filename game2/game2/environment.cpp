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
    character = new Character(sdl_setup, characterImage, 100, 150, this);
    
    wallImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/horWall.png");
    horWall = new Wall(sdl_setup, wallImage, 512, 100, 100, 1024, this);
    horWall1 = new Wall(sdl_setup, wallImage, 512, 300, 100, 1024, this);
    horWall2 = new Wall(sdl_setup, wallImage, 512, 500, 100, 1024, this);
    horWall3 = new Wall(sdl_setup, wallImage, 512, 700, 100, 1024, this);
    horWall4 = new Wall(sdl_setup, wallImage, 512, 900, 100, 1024, this);
    
    
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
    delete horWall;
    delete horWall1;
    delete horWall2;
    delete horWall3;
    delete horWall4;
}

void Environment::DrawBack()
{
    
    if(((horWall->getWallY())+(.5 * horWall->getWallH()) > (character->getCharacterY()+(character->getCharacterH()*.5)))){
        character->Draw();
    }
    
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        if((*i)->getCharacterY() < (horWall->getWallY() +  (*i)->getCharacterH())){
            (*i)->Draw();
        }
    }
    
    horWall->Draw();
    horWall2->Draw();
    horWall3->Draw();
    horWall4->Draw();
    horWall1->Draw();
//    std::cout << "wall y " << horWall->getWallY() << "\n";
//    std::cout << "c y " << character->getCharacterY() << "\n";
    
    for (std::vector<NPC*>::iterator i = npcList.begin(); i != npcList.end(); ++i)
    {
        if((*i)->getCharacterY() > (horWall->getWallY() +  (*i)->getCharacterH())){
            (*i)->Draw();
        }
    }
    
    if(((horWall->getWallY())+(.5 * horWall->getWallH()) < (character->getCharacterY()+(character->getCharacterH()*.5)))){
        character->Draw();
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
