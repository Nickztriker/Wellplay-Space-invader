#pragma once
#include <raylib.h>

class Laser {
    public:
      Laser(Vector2 position, int speed); //set position and speed of laser
      void Update();
      void Draw();
      Rectangle getRect();
      bool active;
    private:
      Vector2 position; 
      int speed;

};