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
        void resetStats();
        void loadHighScore();
        void saveHighScore();

        unsigned int        shipsLeft;
        bool                gameActive;
        unsigned int        score;
        unsigned int        highScore;
        unsigned int        level;

    private:
        AlienInvasion*      _game;
        std::string         _highScoreFilePath;
};
