#include <raylib.h>
#include "game.hpp"
#include <string> //[Add Score] ใช้เพราะ score เป็น string

//[Add Score] ฟังก์ชัน score
std::string FormatWithLeadingZeros(int number, int width) {
    std::string numberText = std::to_string(number);
    int leadingZeros = width - numberText.length();
    return numberText = std::string(leadingZeros, '0') + numberText;
}
///

int main()
{
    
    InitAudioDevice();//[Add Sounds]

    while(WindowShouldClose() == false) {
        UpdateMusicStream(game.music); //[Add Sounds]
        //[Add Score] : Display Score on the screen (ฟอนต์,คำ,{ขนาด,ขนาด})
        DrawTextEx(font, "SCORE", {50, 15}, 34, 2, yellow);
        std::string scoreText = FormatWithLeadingZeros(game.score, 5); //เรียกใช้ function FormatWithLeadingZeros 
        DrawTextEx(font, scoreText.c_str(), {50, 40}, 34, 2, yellow);

        //[Add Highscore] Display Highscore on the screen
        DrawTextEx(font, "HIGH-SCORE", {570, 15}, 34, 2, yellow);
        std::string highscoreText = FormatWithLeadingZeros(game.highscore, 5);
        DrawTextEx(font, highscoreText.c_str(), {655, 40}, 34, 2, yellow);

        game.Draw();
        EndDrawing();
    }

    CloseAudioDevice();//[Add Sounds]ปิดเสียงเมื่อออกเกม
}