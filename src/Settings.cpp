#include "Settings.hpp"

Settings::Settings()
{
    // initialize the settings that don't change during the game
    // screen settings
    screenWidth = 1200;
    screenHeight = 800;
    bgColor = sf::Color::Black;

    // ship settings
    shipLimit = 3;

    // bullet settings
    bulletWidth = 1200;
    bulletHeight = 12;
    bulletColor = sf::Color::White;
    bulletMaxCount = 5;

    // alien settings
    fleetDropSpeed = 200;

    // how quickly the game speeds up
    speedUpScale = 1.1;

    initializeDynamicSettings();
}

void Settings::initializeDynamicSettings()
{
    // initialize the settings that change during the game
    shipSpeed = 10;
    bulletSpeed = 5;
    alienSpeed = 1;

    // 1 represents right, -1 represents left
    fleetDirection = 1;

    // scoring
    alienPoints = 10;
}

void Settings::increaseSpeed()
{
    shipSpeed *= speedUpScale;
    bulletSpeed *= speedUpScale;
    alienSpeed *= speedUpScale;
}
