#include "Scoreboard.hpp"
#include "AlienInvasion.hpp"

Scoreboard::Scoreboard(AlienInvasion* game) : _game(game), _score(0)
{
    if (!_font.loadFromFile("assets/fonts/audiowide.ttf"))
        throw std::runtime_error("Failed to load audiowide font");
    _scoreText.setFont(_font);
    _scoreText.setCharacterSize(20);
    _scoreText.setFillColor(sf::Color::White);

    updateScoreText();

    // display the score at the top right of the screen
    _scoreText.setPosition(_game->settings.screenWidth - _scoreText.getGlobalBounds().width - 20, 20);
}

void Scoreboard::updateScoreText()
{
    _scoreText.setString("Score: " + std::to_string(_score));
}

void Scoreboard::showScore()
{
    _game->window.draw(_scoreText);
}
