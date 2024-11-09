#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <memory>

class AlienInvasion;
class Ship;

class Scoreboard
{
    public:
        Scoreboard(AlienInvasion* game);
        void updateScore();
        void checkHighScore();
        void updateLevel();
        void updateShipsLeft();
        void draw();

        std::vector<std::unique_ptr<Ship>> ships;

    private:
        void updateHighScore();
        std::string formatWithCommas(unsigned int value);

        AlienInvasion*  _game;
        sf::Text        _scoreText;
        sf::Text        _highScoreText;
        sf::Text        _levelText;
};
