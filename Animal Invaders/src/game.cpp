#include "game.hpp"
#include <iostream>
#include <fstream>
using namespace std;

Game::Game()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20); // set interval min to max in milliseconds
    itemSpawnInterval = GetRandomValue(10, 15);
    lives = 3;
    diecounter = 0;
    roundcounter = 1;
    run = true;
    
    music = LoadMusicStream("sounds/slow-world.ogg");
    explosionSound = LoadSound("sounds/explosion.ogg");
    levelupSound = LoadSound("sounds/levelup.ogg");
    laserlinebar = LoadSound("sounds/roddeelaser.ogg");
    spaceshiphurt = LoadSound("sounds/classic_hurt.ogg");
    
    SetMusicVolume(music, 0.25f);
    SetSoundVolume(explosionSound, 0.5f);
    SetSoundVolume(laserlinebar, 0.75f);
    SetSoundVolume(spaceshiphurt, 0.75f);

    PlayMusicStream(music);
    

    InitGame();
}

Game::~Game(){
    Alien::UnloadImages();
    UnloadMusicStream(music);
}

void Game::Update(){
    
    
    if(run) {

        double currentTime = GetTime();
        if(currentTime - timeLastSpawn > mysteryShipSpawnInterval) { //ถ้าเวลาปัจจุบัน - เวลาที่ยาน spawn ล่าสุด > ค่า interval ของ mys.ship (หายนานเกินไป)
            mysteryship.Spawn(); // spawn ยานขึ้นมา
            timeLastSpawn = GetTime(); //ตั้งให้เวลาที่ยาน spawn ล่าสุดเป็นค่าเวลาปัจจุบัน
            mysteryShipSpawnInterval = GetRandomValue(10, 20); //set interval same as in Game class
        }

        double currentTime2 = GetTime();
        if(currentTime2 - timeitemlastSpawn > itemSpawnInterval ) {
            fallingitems.Spawn();
            timeitemlastSpawn = GetTime();
            itemSpawnInterval = GetRandomValue(10, 15);
        } 

        for(auto& laser: spaceship.lasers){
            laser.Update();
        }
        
        MoveAliens();
        AlienShootlaser();

        for(auto& laser: alienLasers) {
            laser.Update();
        }

        DeleteInactiveLasers();
        
        mysteryship.Update();

        fallingitems.Update();
        
        CheckForCollisions();

    } else {
        if(IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
            
        }
    }
}

void Game::Draw(){
    spaceship.Draw();

    for(auto& laser: spaceship.lasers) { //เป็น loop ให้ laser โดน draw ขึ้นเรื่อยๆ
        laser.Draw();
    }

    for(auto& obstacle: obstacles) {
        obstacle.Draw();
    }

    for(auto& alien: aliens) {
        alien.Draw();
    }

    for(auto& laser: alienLasers) {
        laser.Draw();
    }

    mysteryship.Draw();
    fallingitems.Draw();
    
}

void Game::HandleInput(){

    if(run) {
        if(IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
        spaceship.MoveLeft();
        } else if(IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            spaceship.MoveRight();
        } else if(IsKeyDown(KEY_SPACE)) {
            spaceship.FireLaser();
        }
    }
}

void Game::DeleteInactiveLasers()
{
    for(auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();){
        if(!it -> active) {
            it = spaceship.lasers.erase(it);
        } else {
            ++ it;
        }
    }

    for(auto it = alienLasers.begin(); it != alienLasers.end();){
        if(!it -> active) {
            it = alienLasers.erase(it);
        } else {
            ++ it;
        }
    }
}

vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 3;
    float gap = (GetScreenWidth() - (4 * obstacleWidth))/5;

    for(int i = 0; i < 4; i++) {
        float offsetX = (i + 1) * gap + i * obstacleWidth; //calculates the horizontal position of each obstacle by adding equal gap between them
        obstacles.push_back(Obstacle({offsetX, float(GetScreenHeight() - 200)}));
    }
    return obstacles;
    
}

vector<Alien> Game::CreateAliens()
{
    vector<Alien> aliens;
    for(int row = 0; row < 6; row++) {
        for(int column = 0; column < 11; column++) {
            int alienType;
            
            if(row == 0) {
                alienType = 1;
            } else if (row == 1 || row == 2) {
                alienType = 2;
            } else if (row == 3 || row == 4 || row == 5){
                alienType = 3;
            }

            float x = 75 + column * 55;
            float y = 100 + row * 55;
            aliens.push_back(Alien(alienType, {x, y}));
        }
    }
    return aliens;
}

void Game::MoveAliens() {
    for(auto& alien: aliens) {
        if(alien.position.x + alien.alienImages[alien.type -1].width > GetScreenWidth() - 25)
        {
            aliensDirection = -2.0;
            MovedownAliens(4.5);
        }
        if(alien.position.x < 25) {
            aliensDirection = 2.0;
            MovedownAliens(4.5);
        }
        
        alien.Update(aliensDirection);
    }


}

void Game::MovedownAliens(double distance)
{
    for(auto& alien: aliens) {
        alien.position.y += distance;
    }
}

void Game::AlienShootlaser()
{
    double currentTime = GetTime();
    if(currentTime - timeLastAlienFired >= alienLaserShootInterval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1); // กำหนดค่า random มาเป็น Index เพื่อยิงคำสั่งให้ aliens บางตัวยิง laser
        Alien& alien = aliens[randomIndex];
        alienLasers.push_back(Laser({alien.position.x + alien.alienImages[alien.type -1].width/2, alien.position.y + alien.alienImages[alien.type -1].height}, 8));

        timeLastAlienFired = GetTime();
    }
}

void Game::CheckForCollisions()
{
    //Spaceship Lasers

    for(auto& laser: spaceship.lasers) {
        auto it = aliens.begin(); //create iterator and made it point to the beginning of aliens vector
        while(it != aliens.end()) { //ในช่วงที่ point จาก begin ไปยัง end ของ vector aliens
            if(CheckCollisionRecs(it -> getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);

                if(it -> type == 1) {
                    score += 300;
                } else if (it -> type == 2) {
                    score += 200;
                } else if (it -> type == 3) {
                    score += 100;
                } else if (it -> type == 4) {
                    score += 50;
                } else if (it -> type == 5) {
                    score += 25;
                }
                
                CheckForHighscore();

                it = aliens.erase(it);
                laser.active = false;
            } else {
                ++it;
            }
        }

        if(aliens.empty()) {
            GameOver();
        }

        for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    it++;
                }
            }

        }

        if(CheckCollisionRecs(mysteryship.getRect(), laser.getRect())){
            mysteryship.alive = false;
            laser.active = false;
            score += 500;
            CheckForHighscore();
            PlaySound(explosionSound);
        }

        if(CheckCollisionRecs(fallingitems.getRect(), laser.getRect())){
            fallingitems.alive = false;
            laser.active = false;
            spaceship.FireLaser2();
            PlaySound(laserlinebar);
        }
    }

    //Alien Lasers

    for(auto& laser: alienLasers) {
        if(CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives --;
            PlaySound(spaceshiphurt);
            if(lives == 0) {
                GameOver();
                diecounter++;
            }
        }

        for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), laser.getRect())){
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                } else {
                    it++;
                }
            }

        }
    }
    
    //Alien Collision with Obstacle

    for(auto& alien: aliens) {
        for(auto& obstacle: obstacles) {
            auto it = obstacle.blocks.begin();
            while(it != obstacle.blocks.end()){
                if(CheckCollisionRecs(it -> getRect(), alien.getRect())) {
                    it = obstacle.blocks.erase(it);
                } else {
                    it++;
                }
            }

        }

        if(CheckCollisionRecs(alien.getRect(), spaceship.getRect())) {
            GameOver();
        }
    }

    //item Collision with spaceship

    if(CheckCollisionRecs(fallingitems.getRect(), spaceship.getRect())){
        fallingitems.alive = false;
        lives += 2;
        PlaySound(levelupSound);
    }
}

void Game::GameOver()
{
    run = false;
    roundcounter++;
}

void Game::InitGame()
{
    obstacles = CreateObstacles();
    aliens = CreateAliens();
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    mysteryShipSpawnInterval = GetRandomValue(10, 20); // set interval min to max in milliseconds
    lives = 3;
    score = 0;
    
    run = true;
    highscore = loadHighscoreFromFile();
}

void Game::CheckForHighscore()
{
    if(score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

void Game::ResetFallingItems()
{
    fallingitems.alive = false;
}

int Game::saveHighscoreToFile(int highscore)
{
    ofstream highscoreFile("highscore.txt"); // file open for some write on "highscore.txt" 
    if(highscoreFile.is_open()){
        highscoreFile << highscore;
        highscoreFile.close();
    } else {
        cerr << "Failed to save highscore to file" << endl; //cerr is c++ standard error stream. using in case that cannot load,open or write data.
    }
    return highscore;
}

int Game::loadHighscoreFromFile() 
{
    int loadedHighscore = 0;
    ifstream highscoreFile("highscore.txt"); // to read file name "highscore.txt"
    if(highscoreFile.is_open()) {
        highscoreFile >> loadedHighscore;
        highscoreFile.close();
    } else {
        cerr << "Failed to save highscore from file" << endl; //cerr is c++ standard error stream. using in case that cannot load,open or write data.
    }
    return loadedHighscore;
}

void Game::Reset(){
    spaceship.Reset();
    aliens.clear();
    alienLasers.clear();
    obstacles.clear();
    ResetFallingItems();
}