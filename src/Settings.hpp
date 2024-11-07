#pragma once

#include <SFML/Graphics.hpp>

class Settings
{
    public:
        Settings();

        // screen settings
        unsigned int    screenWidth;
        unsigned int    screenHeight;
        sf::Color       bgColor;

        // ship settings
        float           shipSpeed;
        unsigned int    shipLimit;

        // bullet settings
        float           bulletSpeed;
        unsigned int    bulletWidth;
        unsigned int    bulletHeight;
        sf::Color       bulletColor;
        unsigned int    bulletMaxCount;

        // alien settings
        float           alienSpeed;
        float           fleetDropSpeed;
        int             fleetDirection;
};
