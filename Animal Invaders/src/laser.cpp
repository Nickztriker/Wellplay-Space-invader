#include "laser.hpp"
#include <iostream>
using namespace std;

Laser::Laser(Vector2 position, int speed)
{
    this -> position = position; // set ค่า ให้ exist
    this -> speed = speed;
    active = true; // laser existing
}

void Laser::Draw() {
    if(active)
        DrawRectangle(position.x, position.y, 4, 15, {255,255,0,255});
}

Rectangle Laser::getRect()
{
    Rectangle rect;
    rect.x = position.x;
    rect.y = position.y;
    rect.width = 4;
    rect.height = 15;
    return rect;
}

void Laser::Update() {
    position.y += speed;
    if(active){
         if(position.y > GetScreenHeight() - 50 || position.y < 25){ // ถ้า laser ออกนอกจอไปแล้ว หรือ ค่าพิกัด y < 0
            active = false;
         }
    }
}