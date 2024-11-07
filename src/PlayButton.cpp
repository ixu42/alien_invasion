#include "PlayButton.hpp"
#include "AlienInvasion.hpp"

PlayButton::PlayButton(AlienInvasion* game) : _game(game), _settings(game->settings)
{
    if (!_font.loadFromFile("assets/fonts/audiowide.ttf"))
        throw std::runtime_error("Failed to load audiowide font");
    _buttonWidth = 200;
    _buttonHeight = 50;

    // set up the button
    _button.setSize(sf::Vector2f(_buttonWidth, _buttonHeight));
    _button.setPosition((_settings.screenWidth - _buttonWidth) / 2, (_settings.screenHeight - _buttonHeight) / 2);
    _button.setFillColor(sf::Color(0, 255, 0));

    _button.setOutlineColor(sf::Color(255, 255, 0));
    _button.setOutlineThickness(5);

    // set up the text
    _buttonText.setFont(_font);
    _buttonText.setString("Play");
    _buttonText.setCharacterSize(32);
    _buttonText.setFillColor(sf::Color::White);

    std::cout << "Button text left: " << _buttonText.getLocalBounds().left << std::endl;
    std::cout << "Button text top: " << _buttonText.getLocalBounds().top << std::endl;
    std::cout << "Button text width: " << _buttonText.getLocalBounds().width << std::endl;
    std::cout << "Button text height: " << _buttonText.getLocalBounds().height << std::endl;

    // center the text within the button
    sf::FloatRect textBounds = _buttonText.getLocalBounds();
    _buttonText.setOrigin(textBounds.left + textBounds.width / 2, 
                            textBounds.top + textBounds.height / 2);
    _buttonText.setPosition(_button.getPosition().x + _buttonWidth / 2, 
                            _button.getPosition().y + _buttonHeight / 2);
}

void PlayButton::draw()
{
    _game->window.draw(_button);
    _game->window.draw(_buttonText);
}
