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
        void checkHighScore();
        void updateLevel();

    private:
        AlienInvasion*  _game;
        sf::Font        _font;
        sf::Text        _scoreText;
        sf::Text        _highScoreText;
        sf::Text        _levelText;

        void updateHighScore();
        std::string formatWithCommas(unsigned int value);
};
