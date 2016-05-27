#include "main.hpp"
#include <math.h>

Main::Main() //Constructor
{
    SDL_Init(SDL_INIT_EVERYTHING); //Initialize everything in SDL
    quit = false; //boolean for game loop
    start = false;
    quitEarly = true;
    sdl_setup = new SDL_Setup(&quit);
}

Main::~Main() //Destructor
{
    //avoids memory leaks
    delete sdl_setup;
    delete gameMap;
    
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
    
    
    floor = new Sprite(sdl_setup->GetRenderer(), "images/grass.png", 0, 0, 1024, 768); //map, one big grass tile
    gameMap = new Environment(sdl_setup, floor, this);
    
    
    while (!quit && (sdl_setup->GetEv()->type != SDL_QUIT)) //the game loop
    {
        sdl_setup->Begin();
        
        gameMap->DrawBack();
        
        gameMap->Update();
        
        sdl_setup->End();
    }
}

void Main::endGame(int loser)
{
    quitEarly = false; //winner decided, so allow display of endgame screen
    quit = true;
}
