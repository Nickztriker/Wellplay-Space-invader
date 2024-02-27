#pragma once
#include "spaceship.hpp"
#include "obstacle.hpp"
#include "alien.hpp"
#include "mysteryship.hpp"

class Game {
    public:
        int score; //[Add Score]ประกาศตัวแปร score
        int highscore; //[Add Highscore]
        Music music; //[Add Sounds]

    private:
        void checkForHighscore();//[Add Highscore] 
        void saveHighscoreToFile(int highscore); //[Add Highscore]
        int loadHighscoreFromFile(); //[Add Highscore]
        Sound explosionSound;//[Add Sounds] Explosion Sound
        
};