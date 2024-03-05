#pragma once // ให้ header files รวมอยู่ในการ compile รอบเดียว
#include <raylib.h>
#include "laser.hpp"
#include <vector>
using namespace std;

class Spaceship{
    public:
        Spaceship();
        ~Spaceship();
        void Draw();
        void MoveLeft();
        void MoveRight();
        void FireLaser();
        void FireLaser2();
        Rectangle getRect();
        void Reset();
        vector<Laser> lasers; // attribute ที่ hold all lasers
        Texture2D image;
        Vector2 position; //represent position of spaceship
        double lastFireTime;
        Sound lasersound;
        double startTime;
};