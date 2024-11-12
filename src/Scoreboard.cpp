#include "Scoreboard.hpp"
#include "AlienInvasion.hpp"
#include "Ship.hpp"

Scoreboard::Scoreboard(AlienInvasion* game) : _game(game)
{
    _scoreText.setFont(_game->getResourceManager().getFont("audiowide"));
    _scoreText.setCharacterSize(20);
    _scoreText.setFillColor(sf::Color::White);
    updateScore();

    _highScoreText.setFont(_game->getResourceManager().getFont("audiowide"));
    _highScoreText.setCharacterSize(20);
    _highScoreText.setFillColor(sf::Color::White);
    updateHighScore();

    _levelText.setFont(_game->getResourceManager().getFont("audiowide"));
    _levelText.setCharacterSize(20);
    _levelText.setFillColor(sf::Color::White);
    updateLevel();

    updateShipsLeft();
}

void Scoreboard::updateScore()
{
    _scoreText.setString("Score: " + formatWithCommas(_game->getStats().getScore()));

    // position the score at the top right of the screen
    _scoreText.setPosition(_game->getSettings().screenWidth - 
                            _scoreText.getLocalBounds().width - 10, 10);
}

void Scoreboard::updateHighScore()
{
    _highScoreText.setString("High Score: " + formatWithCommas(_game->getStats().getHighScore()));

    // position the high score at the top center of the screen
    sf::FloatRect textBounds = _highScoreText.getLocalBounds();
    _highScoreText.setOrigin(textBounds.left + textBounds.width / 2, 0);
    _highScoreText.setPosition(_game->getSettings().screenWidth / 2, 10);
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
    if (_game->getStats().getScore() > _game->getStats().getHighScore())
    {
        _game->getStats().setHighScore(_game->getStats().getScore());
        updateHighScore();
    }
}

void Scoreboard::updateLevel()
{
    _levelText.setString("Level: " + std::to_string(_game->getStats().getLevel()));

    // position the level below the score
    _levelText.setPosition(_game->getSettings().screenWidth - 
                            _levelText.getLocalBounds().width - 10,
                            _scoreText.getPosition().y + 
                            _scoreText.getLocalBounds().height + 10);
}

void Scoreboard::updateShipsLeft()
{
    unsigned int shipsLeft = _game->getStats().getShipsLeft();
    _ships.clear();

    for (unsigned int i = 0; i < shipsLeft; ++i)
    {
        auto ship = std::make_unique<Ship>(_game);
        ship->sprite.setScale(0.5f, 0.5f);
        ship->sprite.setPosition(10 + i * ship->sprite.getGlobalBounds().width, 10);
        _ships.push_back(std::move(ship));
    }
}

void Scoreboard::draw()
{
    _game->getWindow().draw(_scoreText);
    _game->getWindow().draw(_highScoreText);
    _game->getWindow().draw(_levelText);
    for (auto& ship : _ships)
        _game->getWindow().draw(ship->sprite);
}
