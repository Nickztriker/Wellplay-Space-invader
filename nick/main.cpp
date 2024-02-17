#include <raylib.h>

int main()
{
    // **Game Loop**

    Color dark_blue = {35,83,125,255};
    int windowWidth = 750;
    int windowHeight = 700; // กำหนดขนาด window

    //create game windown function include 3 things : width, height, title
    InitWindow(windowWidth, windowHeight, "Space Invaders by C++ from Wellplay");
    SetTargetFPS(60); // set fps ไว้ แล้วแต่ hz จอ

    while(WindowShouldClose() == false) {
        
        BeginDrawing(); //create blank canvas to put on object

        ClearBackground(dark_blue);

        EndDrawing(); //end canvas drawing
        

    }

    CloseWindow();
}
