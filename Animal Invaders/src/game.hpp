#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"
#include "game.hpp"
#include "iostream"
#include "fallingdownitem.hpp"
using namespace std;

class Game{
    public:
        Game();
        ~Game();
        void Draw();
        void Update();
        void HandleInput();
        bool run;
        int lives;
        int score;
        int highscore;
        int diecounter;
        int roundcounter;
        Music music;
    
    private:
        void DeleteInactiveLasers();
        Spaceship spaceship;
        vector<Obstacle> CreateObstacles();
        vector<Alien> CreateAliens();
        void MoveAliens();
        void MovedownAliens(double distance);
        void AlienShootlaser();
        void CheckForCollisions();
        void GameOver();
        void Win();
        void Reset();
        void InitGame(); // ทำให้ทุก elements คืนค่าเป็น default เมื่อจะเริ่มเล่นใหม่
        void CheckForHighscore();
        void ResetFallingItems();
        int saveHighscoreToFile(int highscore); // save highscore
        int loadHighscoreFromFile(); // load highscore ทุกครั้งที่มีการเล่นรอบใหม่
        vector<Obstacle> obstacles;
        vector<Alien> aliens;
        double aliensDirection;
        vector<Laser> alienLasers;
        constexpr static float alienLaserShootInterval = 0.3; // constexpr ใช้ระบุตัวแปรนั้นๆว่าเป็นการประกาศค่าแบบคงที่ และสามารถเป็นค่าเริ่มต้นได้เมื่อ compile
        float timeLastAlienFired;
        MysteryShip mysteryship;
        float mysteryShipSpawnInterval; // hold the interval mys.which ship will appear (won't be constant)
        float timeLastSpawn; // hold the time mys.ship was spawned
        
        Sound explosionSound;
        Sound levelupSound;
        Sound laserlinebar;
        Sound spaceshiphurt;
        
        FallingItems fallingitems;
        
        float itemSpawnInterval;
        float timeitemlastSpawn;
};