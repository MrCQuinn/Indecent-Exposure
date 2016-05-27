#include "main.hpp"
#include <cmath>
#include <thread>

Main::Main() //Constructor
{
    SDL_Init(SDL_INIT_EVERYTHING); //Initialize everything in SDL
    quit = false; //boolean for game loop
    start = false;
    quitEarly = true;
    sdl_setup = new SDL_Setup(&quit);
    level = 1;
}

Main::~Main() //Destructor
{
    //avoids memory leaks
    delete sdl_setup;
    delete levelOne;
    delete splash;
    
    SDL_Quit();
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
        if (sdl_setup->GetEv()->type == SDL_KEYDOWN)
        {
            if (sdl_setup->GetEv()->key.keysym.sym == SDLK_SPACE)
            {
                delete splash;
                splash = new Sprite(sdl_setup->GetRenderer(), "images/InstructionSplash.png", 0, 0, 1024, 768);
            }
            if(sdl_setup->GetEv()->key.keysym.sym == SDLK_s){
                start = true;
            }
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
    levelOne = new Environment(sdl_setup, floor, this);
    
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
    levelOne->addWall(270, 445, 461, 461); //first part of third wall
    levelOne->addWall(508, 445, 800, 461); //second part of third wall
    levelOne->addWall(844, 445, 1080, 461); //third part of third wall
    levelOne->addWall(270, 450, 338, 595);//vertwall
    levelOne->addWall(270, 500, 1080, 595); // fourth wall
    
    levelOne->addNPC(new NPC(sdl_setup, NPCBoyImage, 300, 400, levelOne, 1, 200));
    levelOne->addNPC(new NPC(sdl_setup, NPCBoyImage, 500, 400, levelOne, 2, 200));
    levelOne->addNPC(new NPC(sdl_setup, NPCGirlImage, 700, 200, levelOne, 2, 200));
    levelOne->addNPC(new NPC(sdl_setup, NPCPrincipalImage, 700, 420, levelOne, 3, 400));
    
    

    
    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        timeOfNextUpdate = SDL_GetTicks() + 17;
        
        sdl_setup->Begin();
        
        if(level == 1){
            levelOne->DrawBack();
        
            levelOne->Update();
            
            if(levelOne->isComplete()){
                level++;
            }
        }
        
        
        sdl_setup->End();
        
        timeLeft = timeOfNextUpdate - SDL_GetTicks();
        if(timeLeft > 0){
            std::this_thread::sleep_for(std::chrono::milliseconds(timeLeft));
        }
    }
}

void Main::endGame(int loser)
{
    quitEarly = false; 
    quit = true;
}
