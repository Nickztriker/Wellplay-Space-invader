#include <raylib.h>
#include "game.hpp"
#include <string>
using namespace std;

string FormatWithLeadingZeros(int number, int width) {
    string numberText = to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = string(leadingZeros, '0') + numberText;
}

int main()
{
    // **Game Loop**

    Color bright_purple = {145,115,255,255};
    Color yellow = {255,237,50,255};
    float offset = 50;
    float windowWidth = 750;
    float windowHeight = 700; // กำหนดขนาด window

    //create game windown function include 3 things : width, height, title
    InitWindow(windowWidth + offset, windowHeight + 2*offset, "Animal Invaders by C++ from Wellplay");
    InitAudioDevice(); // setup audio and prepare to use in game
    Font font = LoadFontEx("font/monogram.tff", 64, 0, 0); //64 = font size
    Texture2D spaceshipImage = LoadTexture("graphics/friedegg_icon.png"); 
    Texture2D background = LoadTexture("graphics/background.png");
    
    // Background position
    float backgroundY = 0;

    // Scrolling speed
    float scrollSpeed = 1.0f;

    SetTargetFPS(60); // set fps ไว้ แล้วแต่ hz จอ

    Game game;
    
    while(WindowShouldClose() == false) {
        
        UpdateMusicStream(game.music);
        game.HandleInput();
        game.Update();
        
        // Scroll the background down
        backgroundY += scrollSpeed;

        // If the background has scrolled off the screen, reset its position
        if (backgroundY >= background.height) {
            backgroundY = 0;
        }
        
        BeginDrawing(); //create blank canvas to put on object

        ClearBackground(GetColor(0x052c46ff));
        // Draw background
        DrawTexture(background, 0, 0, DARKBLUE);

        // Draw background at its current position
        DrawTextureRec(background, Rectangle{0, backgroundY, windowWidth + offset, background.height - backgroundY}, {0, 0}, DARKBLUE);

        // Draw the rest of the background (to fill the remaining space at the top)
        if (backgroundY > 0) {
           DrawTextureRec(background, Rectangle{0, 0, windowWidth + offset, backgroundY}, {0, background.height - backgroundY}, DARKBLUE);
        }
        
        DrawRectangleRoundedLines({10,10,780,780}, 0.1f, 20, 2, bright_purple);
        DrawLineEx({25,770},{775,770}, 3, bright_purple); //indicate start&end point of line below spaceship, determine thickness and color.
        
        if(game.run){
            DrawTextEx(font, "ROUND ", {650,747}, 17, 3, yellow);
            string roundCount = FormatWithLeadingZeros(game.roundcounter, 2);
            DrawTextEx(font, roundCount.c_str(), {725,747}, 17, 3, yellow);
        } else {
            DrawTextEx(font, "THE END", {200,350}, 100, 3, yellow);
            DrawTextEx(font, "Press -Enter- to restart", {140,500}, 43, 3, yellow);
        }
        
        float x = 50.0;
        for(int i = 0; i < game.lives; i++) {
            DrawTextureV(spaceshipImage, {x, 735}, WHITE);
            x += 50;
        }

        DrawTextEx(font, "SCORE", {50,25}, 25, 3, yellow);
        string scoreText = FormatWithLeadingZeros(game.score, 5);
        DrawTextEx(font, scoreText.c_str(), {50,50}, 25, 3, yellow);

        DrawTextEx(font, "HIGHSCORE", {600,25}, 25, 3, yellow);
        string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {677,50}, 25, 3, yellow);

        DrawTextEx(font, "DIE : ", {175,25}, 25, 3, yellow);
        string dieCount = FormatWithLeadingZeros(game.diecounter, 3);
        DrawTextEx(font, dieCount.c_str(), {240,25}, 25, 3, yellow);
        
        game.Draw();
        EndDrawing(); //end canvas drawing
        
    }

    UnloadTexture(background);
    CloseWindow();
    CloseAudioDevice();
    
    return 0;
}
