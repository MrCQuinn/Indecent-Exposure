#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "imports.hpp"

class Sprite
{
public:
    Sprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h);
    Sprite(SDL_Renderer* passed_renderer, SDL_Texture* passed_image, int x, int y, int w, int h);
    ~Sprite();
    
    void Draw();
    void SetX(float x);
    void SetY(float y);
    void SetPosition(float x, float y);
    float GetX();
    float GetY();
    int GetWidth();
    int GetHeight();
    void SetOrigin(float x, float y);
    void SetUpAnimation(int passed_amount_x, int passed_amount_y);
    void Animation(int beginFrame, int endFrame, int row, float speed);
    void DisplayRectangle(SDL_Texture* healthBar);
    void changeImage(SDL_Texture* passed_image);
    void setCollisionImage(SDL_Texture* passed_collisionImage);
    
private:
    float X_pos;
    float Y_pos;
    float origin_x;
    float origin_y;
    SDL_Texture* image;
    SDL_Texture* collisionImage;
    SDL_Rect rect;
    SDL_Rect crop;
    int img_width;
    int img_height;
    int currentFrame;
    int animationDelay;
    int amount_frame_x;
    int amount_frame_y;
    SDL_Renderer* renderer;
};

#endif // SPRITE_HPP
