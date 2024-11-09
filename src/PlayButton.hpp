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

        sf::RectangleShape  button;

    private:
        AlienInvasion*      _game;
        Settings            _settings;
        float               _buttonWidth;
        float               _buttonHeight;
        sf::Text            _buttonText;
};
