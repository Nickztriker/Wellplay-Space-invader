#include "mysteryship.hpp"

MysteryShip::MysteryShip()
{
    image = LoadTexture("graphics/macky.png");
    alive = false;
}

MysteryShip::~MysteryShip() 
{
    UnloadTexture(image);
}

void MysteryShip::Spawn() {
    position.y = 70; //set spawn point
    int side = GetRandomValue(0, 1); //set random starting point

    if(side == 0) {
        position.x = 25;
        speed = 3;
    } else {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    alive = true;
}

Rectangle MysteryShip::getRect()
{
    if(alive) {
        return {position.x, position.y, float(image.width), float(image.height)}; // ถ้า alive = true ให้ mys.ship มีค่าพิกัดและค่า rectangle ของยาน
    } else {
        return {position.x, position.y, 0, 0};
    }
}

void MysteryShip::Update() {
    if(alive) {
        position.x += speed;
        if(position.x > GetScreenWidth() - image.width - 25|| position.x < 25) { //ถ้าเลยขอบจอ ให้ยานหายไป
            alive = false;
        }
    }
}

void MysteryShip::Draw() {
    if(alive) {
        DrawTextureV(image, position, WHITE);
    }
}