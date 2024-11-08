#include "GameStats.hpp"
#include "AlienInvasion.hpp"

GameStats::GameStats(AlienInvasion* game) : _game(game)
{
    resetStats();
    highScore = 0;
}

void GameStats::resetStats()
{
    shipsLeft = _game->settings.shipLimit;
    gameActive = false;
    score = 0;
}
