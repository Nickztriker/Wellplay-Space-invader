#include "game.hpp"
#include <iostream>
#include <fstream> //[Add Highscore] เรียกข้อมูลจากไฟล์ 


//[Add Sounds]
Game::Game() //เริ่มเกม
{
    music = LoadMusicStream("Sounds/music.ogg"); //Background Sound
    explosionSound = LoadSound("Sounds/explosion.ogg"); //Explosion Sound
    PlayMusicStream(music); //เล่นเพลง
    InitGame();
}
///

//[Add Sounds]
Game::~Game() { //ปิดเกม
    Alien::UnloadImages();
    UnloadMusicStream(music); //Background Sound
    UnloadSound(explosionSound); //Explosion Sound
}
///

void Game::CheckForCollisions()
{
    //Spaceship Lasers

    for(auto& laser: spaceship.lasers) {
        auto it = aliens.begin();
        while(it != aliens.end()){
            if(CheckCollisionRecs(it -> getRect(), laser.getRect()))
            {
                PlaySound(explosionSound); //[Add Sounds]เสียงเมื่อยิงยานศัตรู
                
                //[Add Score]อัพเดต score
                if(it -> type == 1) {
                    score += 100;
                } else if (it -> type == 2) {
                    score += 200;
                } else if(it -> type == 3) {
                    score += 300;
                }
                ///
                checkForHighscore();//[Add Highscore]              
                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }

        for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }

        if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())){
            mysteryship.alive = false;
            laser.active = false;
            
            score += 500; //[Add Score] อัพเดต score ยานใหญ่
            checkForHighscore();//[Add Highscore]          
            PlaySound(explosionSound);//Add Sounds
            
        }
    }

    //Alien Lasers

    for(auto& laser: alienLasers) {
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())){
            laser.active = false;
            lives --;
            if(lives == 0) {
                GameOver();
            }
        }

          for(auto& obstacle: obstacles){
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    ++it;
                }
            }
        }
    }

    //Alien Collision with Obstacle
    
    for(auto& alien: aliens) {
        for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()) {
                if(CheckCollisionRecs(it -> getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    it ++;
                }
            }
        }

        if(CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    lives = 3;
    score = 0; //[Add Score]
    highscore = loadHighscoreFromFile();//[Add Highscore]
    run = true;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);
}
//[Add Highscore]เรียกฟังก์ชันจาก game.hpp
void Game::checkForHighscore()
{
    if(score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);//เซฟhighscore
    }
}
//เช็กค่าhighscoreตลอดเวลา

//[Add Highscore]ฟังก์ชันสำหรับเซฟhighscore
void Game::saveHighscoreToFile(int highscore)
{
    std::ofstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to save highscore to file" << std::endl;
    }
}
///

//[Add Highscore] โหลดhighscore จากไฟล์
int Game::loadHighscoreFromFile() {
    int loadedHighscore = 0;
    std::ifstream highscoreFile("highscore.txt");
    if(highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        std::cerr << "Failed to load highscore from file." << std::endl;
    }
    return loadedHighscore;
}
///

