#pragma once
#include <raylib.h>

class Alien {
    public:
        Alien(int type, Vector2 position);
        void Update(int direction);
        void Draw();
        int GetType();
        static Texture2D alienImages[5]; // สร้าง array ให้ alien 3 ตัว เพื่อไม่ต้องให้โหลดรูปทุกตัว แต่ทุกตัวจะใช้ copy จากตัวแรก (optimize)
        static void UnloadImages(); // unload aliens to free memory
        int type;
        Vector2 position;
        Rectangle getRect();
    private:
};