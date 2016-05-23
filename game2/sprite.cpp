#include "sprite.hpp"

Sprite::Sprite(SDL_Renderer* passed_renderer, std::string FilePath, int x, int y, int w, int h) //Constructor
{
    renderer = passed_renderer;
    image = NULL;
    image = IMG_LoadTexture(renderer, FilePath.c_str());
    
    if (image == NULL) //error checking
    {
        std::cout << "Could not load image" << std::endl;
    }
    
    //location and size
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);
    
    //cropped location and size (used for sprite animation)
    crop.x = 0;
    crop.y = 0;
    crop.w = img_width;
    crop.h = img_height;
    
    //position as double (for distance function)
    X_pos = x;
    Y_pos = y;
    
    //allows for unit to stand directly on top of target, instead of offset
    origin_x = 0;
    origin_y = 0;
    
    currentFrame = 0;
    animationDelay = 0;
    amount_frame_x = 0;
    amount_frame_y = 0;
}

Sprite::Sprite(SDL_Renderer* passed_renderer, SDL_Texture* passed_image, int x, int y, int w, int h)
{
    renderer = passed_renderer;
    image = NULL;
    image = passed_image;
    
    //location and size
    rect.x = x;
    rect.y = y;
    rect.w = w;
    rect.h = h;
    
    SDL_QueryTexture(image, NULL, NULL, &img_width, &img_height);
    
    //cropped location and size (used for sprite animation)
    crop.x = 0;
    crop.y = 0;
    crop.w = img_width;
    crop.h = img_height;
    
    //position as double (for distance function)
    X_pos = x;
    Y_pos = y;
    
    //allows for unit to stand directly on top of target, instead of offset
    origin_x = 0;
    origin_y = 0;
    
    currentFrame = 0;
    animationDelay = 0;
    amount_frame_x = 0;
    amount_frame_y = 0;
    
}

Sprite::~Sprite() //Destructor
{
    SDL_DestroyTexture(image);
}

void Sprite::SetUpAnimation(int passed_amount_x, int passed_amount_y)
{
    amount_frame_x = passed_amount_x;
    amount_frame_y = passed_amount_y;
}

void Sprite::Animation(int beginFrame, int endFrame, int row, float speed)
{
    while (animationDelay+speed < SDL_GetTicks()) //cycle through cropped frames of image
    {
        
        if (endFrame <= currentFrame)
        {
            currentFrame = beginFrame;
        } else {
            currentFrame++;
        }
        
        crop.x = currentFrame * (img_width/amount_frame_x);
        crop.y = row * (img_height/amount_frame_y);
        crop.w = img_width/amount_frame_x;
        crop.h = img_height/amount_frame_y;
        
        animationDelay = SDL_GetTicks();
    }
}

void Sprite::Draw()
{
    SDL_RenderCopy(renderer, image, &crop, &rect);
}

void Sprite::SetX(float x)
{
    X_pos = x;
    rect.x = int(X_pos - origin_x);
}
void Sprite::SetY(float y)
{
    Y_pos = y;
    rect.y = int(Y_pos - origin_y);
}
void Sprite::SetPosition(float x, float y)
{
    X_pos = x;
    Y_pos = y;
    rect.x = int(X_pos - origin_x);
    rect.y = int(Y_pos - origin_y);
}

float Sprite::GetX()
{
    return X_pos;
}
float Sprite::GetY()
{
    return Y_pos;
}

void Sprite::SetOrigin(float x, float y)
{
    origin_x = x;
    origin_y = y;
    
    SetPosition(GetX(), GetY());
}

int Sprite::GetWidth()
{
    return rect.w;
}

int Sprite::GetHeight()
{
    return rect.h;
}

void Sprite::changeImage(SDL_Texture* passed_image)
{
    image = passed_image;
}

void Sprite::setCollisionImage(SDL_Texture* passed_collisionImage) //set health bar to full health
{
    collisionImage = passed_collisionImage;
}
