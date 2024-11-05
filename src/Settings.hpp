#pragma once

#include <SFML/Graphics.hpp>

class Settings
{
    public:
        Settings();

        unsigned int    screenWidth;
        unsigned int    screenHeight;
        sf::Color       bgColor;
        float           shipSpeed;
};
