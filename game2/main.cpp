#include "main.hpp"
#include <cmath>
#include <thread>

Main::Main() //Constructor
{
    SDL_Init(SDL_INIT_EVERYTHING); //Initialize everything in SDL
    quit = false; //boolean for game loop
    start = false;
    pause = false;
    sdl_setup = new SDL_Setup(&quit);
    level = 0;
    startTime = 0;
    timesSeen = new TextMessage(sdl_setup->GetRenderer(), "Times Seen: ", 782, 20);
    
    gameTime = new TextMessage(sdl_setup->GetRenderer(), "Total Game Time: " + std::to_string(SDL_GetTicks()), 750, 2);
    
    //Create item image
    item1Image = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/newShoes.png");
    item2Image = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/newShirt.png");
    item3Image = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/newPants.png");
    
    characterImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/character_big.png");
    characterShoes = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/character_shoes.png");
    characterShirt = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/character_shirt.png");
}

Main::~Main() //Destructor
{
    //avoids memory leaks
    delete sdl_setup;
    delete levelOne;
    delete splash;
    delete timesSeen;
    delete gameTime;
    
    SDL_Quit();
}

void Main::runTests() {
    testAngleMeasure();
    testOctantDetection();
    testLineOfSight();
    testCollision();
    exit(0);
}

void Main::GameLoop()
{
    /*
     * Creates a splash screen and draws it to the screen
     * listens for spacebar or escape
     * Spacebar starts the game, escape starts and quits game
     */
    
    splash = new Sprite(sdl_setup->GetRenderer(), "images/splashScreen.png", 0, 0, 1024, 768); //splash screen
    while (!start)
    {
        sdl_setup->Begin();
        //Listen for key input
        if (sdl_setup->GetEv()->type == SDL_KEYDOWN)
        {
            // d runs tests
            if (sdl_setup->GetEv()->key.keysym.sym == SDLK_d)
            {
                this->runTests();
            }
            // space changes splash
            if (sdl_setup->GetEv()->key.keysym.sym == SDLK_SPACE)
            {
                delete splash;
                splash = new Sprite(sdl_setup->GetRenderer(), "images/InstructionSplash.png", 0, 0, 1024, 768);
            }
            //s starts game and game clock
            if(sdl_setup->GetEv()->key.keysym.sym == SDLK_s){
                start = true;
                startTime = SDL_GetTicks();
            }
            //quits game
            if (sdl_setup->GetEv()->key.keysym.sym == SDLK_ESCAPE)
            {
                start = true;
                quit = true;
            }
        }
        splash->Draw();
        sdl_setup->End();
    }

    /*
     * initializes floor sprite
     * initializes environment for level 1
     *
     * draws and then updates the level object until user quits or ends program
     */
    long timeOfNextUpdate;
    long timeLeft;
    
    floor = new Sprite(sdl_setup->GetRenderer(), "images/grass.png", 0, 0, 1024, 768); //map, one big grass tile
    levelOne = new Environment(sdl_setup, floor, this, 2, 0, characterImage);
    levelTwo = new Environment(sdl_setup, floor, this, 1, 2, characterShirt);
    
    //level 1 stuff
    
    //create level 1 wall stickers here
    wallImage1 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/first_piece.png");
    wallImage2 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/second_piece.png");
    wallImage3 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/third_piece.png");
    wallImage4 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/fourth_piece.png");
    wallImage5 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/fifth_piece.png");
    
    //create NPC images here
    NPCBoyImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/b_student_big.png");
    NPCGirlImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/g_student_sprite.png");
    NPCPrincipalImage = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/principal_sprite.png");
    NPCPrincipalImage2 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/principal_sprite.png");
    
    levelOne->addWallpaper(new Wall(sdl_setup, wallImage1, 512, 45, 90, 1024, levelOne));
    levelOne->addWallpaper(new Wall(sdl_setup, wallImage2, 512, 190, 200, 1024, levelOne));
    levelOne->addWallpaper(new Wall(sdl_setup, wallImage3, 512, 377, 174, 1024, levelOne));
    levelOne->addWallpaper(new Wall(sdl_setup, wallImage4, 512, 531, 134, 1024, levelOne));
    levelOne->addWallpaper(new Wall(sdl_setup, wallImage5, 512, 685, 176, 1024, levelOne));
    
    levelOne->addWall(0, 0, 1024, 90);// top wall
    levelOne->addWall(0,0, 30, 768);//left wall
    levelOne->addWall(0,744, 1024, 768); //bottom wall
    levelOne->addWall(980, 90, 1080, 768); //right wall
    levelOne->addWall(270, 85, 337, 125);  //part of first doorway
    levelOne->addWall(270, 180, 337, 288); //part of first doorway
    levelOne->addWall(757, 85, 823, 125);  //part of second doorway
    levelOne->addWall(757, 180, 823, 288); //part of second doorway
    levelOne->addWall(0,285,820, 290);//second horizontal wall
    levelOne->addWall(270, 445, 461, 463); //first part of third wall
    levelOne->addWall(508, 445, 800, 463); //second part of third wall
    levelOne->addWall(844, 445, 1080, 463); //third part of third wall
    levelOne->addWall(270, 450, 338, 595);//vertwall
    levelOne->addWall(270, 570, 1080, 595); // fourth wall
    
    levelOne->addNPC(new NPC(sdl_setup, NPCGirlImage, 700, 100, levelOne, 2, 350, 100)); //Girl Sprite
    levelOne->addNPC(new NPC(sdl_setup, NPCPrincipalImage, 870, 330, levelOne, 1, 760, 0)); //Principle Sprite
    
    levelOne->addItem(new Items(sdl_setup, item1Image, 375, 480, 64, 64, levelOne)); //Shoes sprite
    levelOne->addItem(new Items(sdl_setup, item2Image, 930, 675, 64, 64, levelOne)); //Shirt sprite
    
    
    //level 2 stuff
    
    wallImage6 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/first_piece_2.png");
    wallImage7 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/second_piece_2.png");
    wallImage8 = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/third_piece_2.png");
    doublelocker = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/double_locker.png");
    locker = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/locker.png");
    vertlocker = IMG_LoadTexture(sdl_setup->GetRenderer(), "images/vert_locker.png");
    
    levelTwo->addWallpaper(new Wall(sdl_setup, wallImage6, 512, 45, 90, 1024, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, doublelocker, 410, 100, 111, 308, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, wallImage7, 512, 189, 198, 1024, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, locker, 605, 240, 111, 160, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, vertlocker, 950, 170, 225, 64, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, doublelocker, 600, 380, 111, 308, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, vertlocker, 950, 400, 225, 64, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, locker, 335, 515, 111, 160, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, locker, 550, 515, 111, 160, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, locker, 413, 640, 111, 160, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, locker, 625, 640, 111, 160, levelTwo));
    levelTwo->addWallpaper(new Wall(sdl_setup, wallImage8, 512, 528, 480, 1024, levelTwo));
    
    levelTwo->addWall(0,210,32,768);//left wall
    levelTwo->addWall(0,0,1080,90);//top wall
    levelTwo->addWall(0,744, 1024, 768); //bottom wall
    levelTwo->addWall(980, 90, 1080, 768); //right wall
    levelTwo->addWall(192, 80, 260, 627); //first vertical wall pt 1
    levelTwo->addWall(192, 690, 260, 768);// first vertical wall pt 2
    levelTwo->addWall(250, 100, 565, 175);// top double locker
    levelTwo->addWall(525, 240, 688, 290);// top locker
    levelTwo->addWall(440, 375, 765, 450);// other double locker
    levelTwo->addWall(260, 535, 420, 575);// second locker
    levelTwo->addWall(470, 535, 650, 575);// one next to it
    levelTwo->addWall(334, 650, 495, 700);// third locker
    levelTwo->addWall(545, 650, 625, 700);// one next to it
    levelTwo->addWall(25, 270, 70, 290);// first doorway1
    levelTwo->addWall(115, 270, 195, 290);// first doorway2
    levelTwo->addWall(755, 90, 825, 130);// second doorway1
    levelTwo->addWall(755, 185, 825, 768);// second doorway2
    levelTwo->addWall(915, 160, 1080, 300);// vert locker 1
    levelTwo->addWall(915, 400, 1080, 535);//vert locker 2
    
    
    levelTwo->addNPC(new NPC(sdl_setup, NPCGirlImage, 710, 200, levelTwo, 2, 350, 100)); //Girl Sprite
    levelTwo->addNPC(new NPC(sdl_setup, NPCBoyImage, 735, 575, levelTwo, 2, 450, 125)); //Boy Sprite
    levelTwo->addNPC(new NPC(sdl_setup, NPCPrincipalImage, 175, 300, levelTwo, 2, 100, 400)); //Principle Sprite
    
    
    levelTwo->addItem(new Items(sdl_setup, item3Image, 930, 675, 64, 64, levelTwo)); //Pants sprite

    levels[0] = levelOne;
    levels[1] = levelTwo;
    
    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        timeOfNextUpdate = SDL_GetTicks() + 17;
        
        sdl_setup->Begin();

        if (!pause) {
            levels[level]->DrawBack();
            levels[level]->Update();
            
            gameTime->Draw("Total Game Time: " + std::to_string((SDL_GetTicks()-startTime)/1000));
            timesSeen->Draw("Times seen: " + std::to_string(levels[level]->timesSeen()));
                
            if(level == 0 && levels[level]->isComplete()){
                level++;
            }
        }
        else {
            splash->Draw();
            if (sdl_setup->GetEv()->key.keysym.sym == SDLK_r)
            {
                pause = false;
            }
            
        }
        //Listen for "q" to quit
        if (sdl_setup->GetEv()->type == SDL_KEYDOWN)
        {
            if (sdl_setup->GetEv()->key.keysym.sym == SDLK_ESCAPE)
            {
                endGame();
            }
            else if (sdl_setup->GetEv()->key.keysym.sym == SDLK_q)
            {
                endGame();
            }
            else if (sdl_setup->GetEv()->key.keysym.sym == SDLK_p)
            {
                pause = true;
                delete splash;
                splash = new Sprite(sdl_setup->GetRenderer(), "images/pauseSplash.png", 0, 0, 1024, 768);
            }
        }
        
        
        sdl_setup->End();
        
        timeLeft = timeOfNextUpdate - SDL_GetTicks();
        if(timeLeft > 0){
            std::this_thread::sleep_for(std::chrono::milliseconds(timeLeft));
        }
    }
}

void Main::winGame()
{
    delete splash;
    splash = new Sprite(sdl_setup->GetRenderer(), "images/WinnerSplash.png", 0, 0, 1024, 768);
    splash->Draw();
    for (;;) {
        if (sdl_setup->GetEv()->type == SDL_KEYDOWN)
        {
            if (sdl_setup->GetEv()->key.keysym.sym == SDLK_ESCAPE)
            {
                endGame();
            }
        }
    }

}

void Main::endGame()
{
    quit = true;
}
