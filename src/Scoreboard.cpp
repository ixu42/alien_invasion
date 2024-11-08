#include "Scoreboard.hpp"
#include "AlienInvasion.hpp"

Scoreboard::Scoreboard(AlienInvasion* game) : _game(game), _score(game->stats.score)
{
    if (!_font.loadFromFile("assets/fonts/audiowide.ttf"))
        throw std::runtime_error("Failed to load audiowide font");
    _scoreText.setFont(_font);
    _scoreText.setCharacterSize(20);
    _scoreText.setFillColor(sf::Color::White);
    updateScore();
}

void Scoreboard::updateScore()
{
    updateScoreText();

    // display the score at the top right of the screen
    _scoreText.setPosition(_game->settings.screenWidth - _scoreText.getLocalBounds().width - 20, 20);
}

void Scoreboard::updateScoreText()
{
    _score = _game->stats.score;
    _scoreText.setString("Score: " + std::to_string(_score));
}

void Scoreboard::showScore()
{
    _game->window.draw(_scoreText);
}
