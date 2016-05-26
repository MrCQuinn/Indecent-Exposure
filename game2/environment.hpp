#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP
#include "imports.hpp"
#include "sdl_setup.hpp"
#include "character.hpp"
#include "wall.hpp"
#include "NPC.hpp"
#include "items.hpp"
#include <vector>
#include "text.hpp"

class Character; //avoids error because Environment includes Character and vice versa
class Building;
class Main;

class Environment
{
public:
    Environment(SDL_Setup* passed_sdl_setup, Sprite* floor, Main* passed_main);
    ~Environment();

	void addWall(int x1, int y1, int x2, int y2);

	/*
	* Returns true if there exists a line of sight between these two points
	* (i.e. no walls in the way)
	*/
	bool LineOfSightExists(int x1, int y1, int x2, int y2);
	/*
	* Returns true if movement from cur position to new position is not blocked
	* (only for horizontal/vertical movement; no diagonal movement)
	*/
	bool Environment::MoveAllowed(int cur_x, int cur_y, int new_x, int new_y);

	void DrawBack();
    void Update();

	bool PixelIsBlocked(int x, int y);
    
    bool isSeen();
	static float GetAngle(int center_x, int center_y, int outside_x, int outside_y);
    
private:
    SDL_Setup* sdl_setup;
    Main* main;
    Sprite* floorSprite;
    SDL_Texture* wallSprite;
    
    int startTime;
    bool showMenu;
    SDL_Texture* characterImage;
    SDL_Texture* NPCBoyImage;
    SDL_Texture* NPCGirlImage;
    SDL_Texture* NPCPrincipalImage;
    SDL_Texture* wallImage1;
    SDL_Texture* wallImage2;
    SDL_Texture* wallImage3;
    SDL_Texture* wallImage4;
    SDL_Texture* wallImage5;
    SDL_Texture* itemImage;
    Items* item;
    Character* character;
    std::vector<NPC*> npcList;
    std::vector<Wall*> wallList;
	char blockedPixels[768][1024]; // It's [y][x]
    int time;
    TextMessage* timesSeen;
    TextMessage* gameTime;
    int seenInt;
    
    
    
};




#endif // ENVIRONMENT_HPP
