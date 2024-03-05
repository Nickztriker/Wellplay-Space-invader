#include "alien.hpp"

Texture2D Alien::alienImages[5] = {};

Alien::Alien(int type, Vector2 position)
{
    this -> type = type;
    this -> position = position;

    if(alienImages[type -1].id == 0){ // optimizing about loading aliens

        switch (type) {
            case 1:
                alienImages[type -1] = LoadTexture("graphics/cow.png");
                break;
            case 2:
                alienImages[type -1] = LoadTexture("graphics/sheep.png");
                break;
            case 3: 
                alienImages[type -1] = LoadTexture("graphics/chicken.png");
                break;
            default:
                alienImages[0] = LoadTexture("graphics/alien_1.png");
                break;
        }
    }
}

void Alien::Draw() {
    DrawTextureV(alienImages[type -1], position, WHITE);
}

int Alien::GetType() {
    return type;
}

void Alien::UnloadImages()
{
    for(int i = 0; i < 4; i++) {
        UnloadTexture(alienImages[i]);
    }
}

Rectangle Alien::getRect()
{
    return {position.x, position.y, float(alienImages[type - 1].width), float(alienImages[type - 1].height)};
}

void Alien::Update(int direction) {
    position.x += direction;
}