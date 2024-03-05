#include "spaceship.hpp"

Spaceship::Spaceship()
{
    image = LoadTexture("graphics/friedegg.png");
    position.x = (GetScreenWidth() - image.width)/2;
    position.y = GetScreenHeight() - image.height - 75;
    lastFireTime = 0.0;
    lasersound = LoadSound("sounds/lasershoot.ogg");
    SetSoundVolume(lasersound, 0.13f);
}

Spaceship::~Spaceship(){
    UnloadTexture(image); // to unload it to clear memory และใช้กับ ~spaceship() เพราะจะถูกเรียกใช้ auto หลังจากปิด game window 
    UnloadSound(lasersound);
}

void Spaceship::Draw() {
    DrawTextureV(image, position, WHITE); // draw image on the screen
}

void Spaceship::MoveLeft() {
    position.x -= 4;
    if(position.x < 25) {
        position.x = 25;
    }
}

void Spaceship::MoveRight() {
    position.x += 4;
    if(position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}

void Spaceship::FireLaser()
{
    if(GetTime() - lastFireTime >= 0.35) { // ใช้ func GetTime() เพื่อ set cooldown ให้ laser
        lasers.push_back(Laser({position.x + image.width/2 - 2,position.y},-6)); // กำหนด position laser เข้าตรงกลางยาน (ที่มี -2 ด้วยเพราะ laser กว้าง 4 px เลยขยับให้มาอยู่ตรงกลางพอดี)
        lastFireTime = GetTime();
        PlaySound(lasersound);
    }
    
}

void Spaceship::FireLaser2()
{
    lasers.push_back(Laser({100,550}, GetRandomValue(-10,-3)));
    //lasers.push_back(Laser({150,550}, GetRandomValue(-10,-3)));
    lasers.push_back(Laser({200,550}, GetRandomValue(-10,-3)));
    //lasers.push_back(Laser({250,550}, GetRandomValue(-10,-3)));
    lasers.push_back(Laser({300,550}, GetRandomValue(-10,-3)));
    //lasers.push_back(Laser({350,550}, GetRandomValue(-10,-3)));
    lasers.push_back(Laser({400,550}, GetRandomValue(-10,-3)));
    //lasers.push_back(Laser({450,550}, GetRandomValue(-10,-3)));
    lasers.push_back(Laser({500,550}, GetRandomValue(-10,-3)));
    //lasers.push_back(Laser({550,550}, GetRandomValue(-10,-3)));
    lasers.push_back(Laser({600,550}, GetRandomValue(-10,-3)));
    //lasers.push_back(Laser({650,550}, GetRandomValue(-10,-3)));
    lasers.push_back(Laser({700,550}, GetRandomValue(-10,-3)));
}

Rectangle Spaceship::getRect()
{
    return {position.x, position.y, float(image.width), float(image.height)};
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width)/ 2.0f;
    position.y = GetScreenHeight() - image.height - 75;
    lasers.clear(); //delete all the lasers the spaceship has fired and are still visible.
}
