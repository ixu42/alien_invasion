#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include "Settings.hpp"

class AlienInvasion;

class PlayButton
{
    public:
        PlayButton(AlienInvasion* game);
        void draw();

    private:
        AlienInvasion*      _game;
        Settings            _settings;
        sf::RectangleShape  _button;
        float               _buttonWidth;
        float               _buttonHeight;
        sf::Text            _buttonText;
        sf::Font            _font;
};
