#pragma once

class AlienInvasion;

class GameStats
{
    public:
        GameStats(AlienInvasion* game);

        unsigned int    shipsLeft;
        bool            gameActive;
        unsigned int    score;
        unsigned int    highScore;
    
        // initialize the stats that can change during the game
        void resetStats();
    private:
        AlienInvasion*  _game;
};
