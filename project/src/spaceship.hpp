#pragma once
#include <raylib.h>

class Spaceship{
    private:
        Texture2D image;
        Vector2 position; //represent position of spaceship
    
    
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();

};