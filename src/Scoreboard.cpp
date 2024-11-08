#include "Scoreboard.hpp"
#include "AlienInvasion.hpp"
#include "Ship.hpp"

Scoreboard::Scoreboard(AlienInvasion* game) : _game(game)
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

    _levelText.setFont(_font);
    _levelText.setCharacterSize(20);
    _levelText.setFillColor(sf::Color::White);
    updateLevel();

    updateShipsLeft();
}

void Scoreboard::updateScore()
{
    _scoreText.setString("Score: " + formatWithCommas(_game->stats.score));

    // position the score at the top right of the screen
    _scoreText.setPosition(_game->settings.screenWidth - _scoreText.getLocalBounds().width - 10, 10);
}

void Scoreboard::updateHighScore()
{
    _highScoreText.setString("High Score: " + formatWithCommas(_game->stats.highScore));

    // position the high score at the top center of the screen
    sf::FloatRect textBounds = _highScoreText.getLocalBounds();
    _highScoreText.setOrigin(textBounds.left + textBounds.width / 2, 0);
    _highScoreText.setPosition(_game->settings.screenWidth / 2, 10);
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

void Scoreboard::checkHighScore()
{
    if (_game->stats.score > _game->stats.highScore)
    {
        _game->stats.highScore = _game->stats.score;
        updateHighScore();
    }
}

void Scoreboard::updateLevel()
{
    _levelText.setString("Level: " + std::to_string(_game->stats.level));

    // position the level below the score
    _levelText.setPosition(_game->settings.screenWidth - _levelText.getLocalBounds().width - 10,
                            _scoreText.getPosition().y + _scoreText.getLocalBounds().height + 10);
}

void Scoreboard::updateShipsLeft()
{
    unsigned int shipsLeft = _game->stats.shipsLeft;
    ships.clear();

    for (unsigned int i = 0; i < shipsLeft; ++i)
    {
        auto ship = std::make_unique<Ship>(_game);
        ship->sprite.setScale(0.5f, 0.5f);
        ship->sprite.setPosition(10 + i * ship->sprite.getGlobalBounds().width, 10);
        ships.push_back(std::move(ship));
    }
}

void Scoreboard::draw()
{
    _game->window.draw(_scoreText);
    _game->window.draw(_highScoreText);
    _game->window.draw(_levelText);
    for (auto& ship : ships)
        _game->window.draw(ship->sprite);
}
