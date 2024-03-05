#include "fallingdownitem.hpp"


FallingItems::FallingItems()
{
    image = LoadTexture("graphics/roddee.png");
    alive = false;
}

FallingItems::~FallingItems()
{
    UnloadTexture(image);
}

void FallingItems::Spawn()
{   
    position.x = GetRandomValue(25,725); //set spawn point
    position.y = 50;
    fallspeed = 4;    
    alive = true;
}

void FallingItems::Update()
{
    if(alive) {
        position.y += fallspeed;
        if(position.y > GetScreenHeight() - image.height - 25 ) { //ถ้าเลยขอบจอล่าง ให้ item หายไป
            alive = false;
        }
    }
}

void FallingItems::Draw() {
    if(alive) {
        DrawTextureV(image, position, WHITE);
    }
}

Rectangle FallingItems::getRect()
{
    if(alive) {
        return {position.x, position.y, float(image.width), float(image.height)};
    } else {
        return {position.x, position.y, 0, 0};
    }
}
