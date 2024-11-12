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

        // getters
        unsigned int getShipsLeft() const { return _shipsLeft; }
        bool isGameActive() const { return _gameActive; }
        unsigned int getScore() const { return _score; }
        unsigned int getHighScore() const { return _highScore; }
        unsigned int getLevel() const { return _level; }

        // setters
        void decrementShipsLeft() { --_shipsLeft; }
        void setGameActive(bool gameActive) { _gameActive = gameActive; }
        void addScore(unsigned int score) { _score += score; }
        void setHighScore(unsigned int highScore) { _highScore = highScore; }
        void incrementLevel() { ++_level; }

    private:
        AlienInvasion*      _game;
        std::string         _highScoreFilePath;
        unsigned int        _shipsLeft;
        bool                _gameActive;
        unsigned int        _score;
        unsigned int        _highScore;
        unsigned int        _level;
};
