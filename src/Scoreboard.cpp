#include "Scoreboard.hpp"
#include "AlienInvasion.hpp"

Scoreboard::Scoreboard(AlienInvasion* game)
    : _game(game), _score(game->stats.score), _highScore(game->stats.highScore)
{
    if (!_font.loadFromFile("assets/fonts/audiowide.ttf"))
        throw std::runtime_error("Failed to load audiowide font");

    _scoreText.setFont(_font);
    _scoreText.setCharacterSize(20);
    _scoreText.setFillColor(sf::Color::White);
    updateScore();

    _highScoreText.setFont(_font);
    _highScoreText.setCharacterSize(20);
    _highScoreText.setFillColor(sf::Color::White);
    updateHighScore();
}

void Scoreboard::updateScore()
{
    _score = _game->stats.score;
    updateScoreText();

    // display the score at the top right of the screen
    _scoreText.setPosition(_game->settings.screenWidth - _scoreText.getLocalBounds().width - 20, 20);
}

void Scoreboard::updateScoreText()
{
    _scoreText.setString("Score: " + formatWithCommas(_score));
}

void Scoreboard::updateHighScore()
{
    _highScore = _game->stats.highScore;
    updateHighScoreText();

    // display the high score at the top center of the screen
    sf::FloatRect textBounds = _highScoreText.getLocalBounds();
    _highScoreText.setOrigin(textBounds.left + textBounds.width / 2, 0);
    _highScoreText.setPosition(_game->settings.screenWidth / 2, 20);
}

void Scoreboard::updateHighScoreText()
{
    _highScoreText.setString("High Score: " + formatWithCommas(_highScore));
}

std::string Scoreboard::formatWithCommas(unsigned int value)
{
    std::string numStr = std::to_string(value);
    int insertPosition = numStr.length() - 3;

    while (insertPosition > 0)
    {
        numStr.insert(insertPosition, ",");
        insertPosition -= 3;
    }

    return numStr;
}

void Scoreboard::showScore()
{
    _game->window.draw(_scoreText);
    _game->window.draw(_highScoreText);
}

void Scoreboard::checkHighScore()
{
    if (_game->stats.score > _game->stats.highScore)
    {
        _game->stats.highScore = _game->stats.score;
        updateHighScore();
    }
}
