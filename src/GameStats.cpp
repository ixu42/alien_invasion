#include "GameStats.hpp"
#include "AlienInvasion.hpp"

GameStats::GameStats(AlienInvasion* game) : _game(game)
{
    resetStats();
}

void GameStats::resetStats()
{
    shipsLeft = _game->settings.shipLimit;
    gameActive = true;
}
