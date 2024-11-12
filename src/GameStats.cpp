#include "GameStats.hpp"
#include "AlienInvasion.hpp"

GameStats::GameStats(AlienInvasion* game) : _game(game)
{
    // initialize the stats that can change during the game
    resetStats();

    _highScore = 0;

    // create the data directory if it doesn't exist
    try
    {
        std::filesystem::create_directories("data");
    }
    catch (const std::exception& e)
    {
        std::cerr << "Failed to create directory /data: " << e.what() << "\n";
        return ;
    }

    _highScoreFilePath = "data/highscore.txt";

    loadHighScore();
}

GameStats::~GameStats()
{
    saveHighScore();
}

void GameStats::resetStats()
{
    _shipsLeft = _game->getSettings().shipLimit;
    _gameActive = false;
    _score = 0;
    _level = 1;
}

void GameStats::loadHighScore()
{
    if (!std::filesystem::exists(_highScoreFilePath))
        return ;

    std::ifstream infile(_highScoreFilePath);
    if (infile.is_open())
    {
        infile >> _highScore;
        infile.close();
    }
    else
        std::cerr << "Failed to open file for reading: " 
            << _highScoreFilePath << "\n";
}

void GameStats::saveHighScore()
{
    std::ofstream outfile(_highScoreFilePath);
    if (outfile.is_open())
        outfile << _highScore;
    else
        std::cerr << "Failed to open file for writing: " 
            << _highScoreFilePath << "\n";
}
