#pragma once

class AlienInvasion;

class GameStats
{
    public:
        GameStats(AlienInvasion* game);

        unsigned int    shipsLeft;
        bool            gameActive;
    
        // initialize the stats that can change during the game
        void resetStats();
    private:
        AlienInvasion*  _game;
};
