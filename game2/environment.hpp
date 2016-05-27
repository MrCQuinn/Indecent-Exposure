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
    friend NPC;
public:
    Environment(SDL_Setup* passed_sdl_setup, Sprite* floor, Main* passed_main, int i);
    Environment();
    ~Environment();

	void addWall(int x1, int y1, int x2, int y2);
    void destroyWall(int x1, int y1, int x2, int y2);

	/*
	* Returns true if there exists a line of sight between these two points
	* (i.e. no walls in the way)
	*/
	bool LineOfSightExists(int x1, int y1, int x2, int y2);
	/*
	* Returns true if movement from cur position to new position is not blocked
	* (only for horizontal/vertical movement; no diagonal movement)
	*/
	bool MoveAllowed(int cur_x, int cur_y, int new_x, int new_y);

	void DrawBack();
    void Update();

	bool PixelIsBlocked(int x, int y);
    
    bool isSeen();
	static float GetAngle(int center_x, int center_y, int outside_x, int outside_y);
    bool isComplete();
    bool backLevel();
    int timesSeen();
    
    void addWallpaper(Wall* wall);
    void addNPC(NPC* npc);
    void addItem(Items* item);
    Character *getCharPointer();
    std::vector<NPC*>* getNPCVector();
    
private:
    SDL_Setup* sdl_setup;
    Main* main;
    Sprite* floorSprite;
    SDL_Texture* wallSprite;
    SDL_Texture* characterImage;
    
    int itemCount;
    int itemsCollected;
    Character* character;
    int caughtCount;
    std::vector<Items*> itemList;
    std::vector<NPC*> npcList;
    std::vector<Wall*> wallList;
	bool blockedPixels[768][1024]; // It's [y][x]
    
    
    
};




#endif // ENVIRONMENT_HPP
