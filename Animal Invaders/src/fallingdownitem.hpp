#pragma once
#include "raylib.h"
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class FallingItems {
    public:
        FallingItems();
        ~FallingItems();
        void Spawn();
        void Update();
        void Draw();
        void generateItem();
        Rectangle getRect();
        bool alive;
        
    private:
        Texture2D image;
        Vector2 position;
        int fallspeed;
        
};