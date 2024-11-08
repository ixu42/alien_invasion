#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

class AlienInvasion;

class GameStats
{
    public:
        GameStats(AlienInvasion* game);
        ~GameStats();

        unsigned int    shipsLeft;
        bool            gameActive;
        unsigned int    score;
        unsigned int    highScore;
        unsigned int    level;

        // initialize the stats that can change during the game
        void resetStats();

        // load the high score from a file
        void loadHighScore();

        // save the high score to a file
        void saveHighScore();

    private:
        AlienInvasion*      _game;
        std::string         _highScoreFilePath;
};
