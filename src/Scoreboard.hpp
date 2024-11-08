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

    private:
        AlienInvasion*  _game;
        sf::Font        _font;
        unsigned int    _score;
        sf::Text        _scoreText;
        unsigned int    _highScore;
        sf::Text        _highScoreText;

        void updateScoreText();
        void updateHighScore();
        void updateHighScoreText();
        std::string formatWithCommas(unsigned int value);
};
