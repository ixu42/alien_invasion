#include "PlayButton.hpp"
#include "AlienInvasion.hpp"

PlayButton::PlayButton(AlienInvasion* game) : _game(game), _settings(game->settings)
{
    if (!_font.loadFromFile("assets/fonts/audiowide.ttf"))
        throw std::runtime_error("Failed to load audiowide font");
    _buttonWidth = 200;
    _buttonHeight = 50;

    // set up the button
    button.setSize(sf::Vector2f(_buttonWidth, _buttonHeight));
    button.setPosition((_settings.screenWidth - _buttonWidth) / 2, (_settings.screenHeight - _buttonHeight) / 2);
    button.setFillColor(sf::Color(0, 255, 0));

    button.setOutlineColor(sf::Color(255, 255, 0));
    button.setOutlineThickness(5);

    // set up the text
    _buttonText.setFont(_font);
    _buttonText.setString("Play");
    _buttonText.setCharacterSize(32);
    _buttonText.setFillColor(sf::Color::White);

    // center the text within the button
    sf::FloatRect textBounds = _buttonText.getLocalBounds();
    _buttonText.setOrigin(textBounds.left + textBounds.width / 2, 
                            textBounds.top + textBounds.height / 2);
    _buttonText.setPosition(button.getPosition().x + _buttonWidth / 2, 
                            button.getPosition().y + _buttonHeight / 2);
}

void PlayButton::draw()
{
    _game->window.draw(button);
    _game->window.draw(_buttonText);
}
