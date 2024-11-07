#pragma once

class AlienInvasion;

class GameStats
{
    public:
        GameStats(AlienInvasion* game);

        int shipsLeft;
    
    private:
        AlienInvasion* _game;

        // initialize the stats that can change during the game
        void resetStats();
};
