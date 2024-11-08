#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class AlienInvasion;

class Scoreboard
{
    public:
        Scoreboard(AlienInvasion* game);
        void updateScore();
        void showScore();

    private:
        AlienInvasion*  _game;
        unsigned int    _score;
        sf::Font        _font;
        sf::Text        _scoreText;

        void updateScoreText();
        std::string formatWithCommas(unsigned int value);
};
