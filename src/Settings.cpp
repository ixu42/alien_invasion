#include "Settings.hpp"

Settings::Settings()
{
    /* initialize the settings that don't change during the game */
    // screen settings
    screenWidth = 1200;
    screenHeight = 800;
    bgColor = sf::Color::Black;

    // ship settings
    shipLimit = 3;
    shipMaxSpeed = 500; // in pixels per second
    shipAcceleration = 2000; // in pixels per second^2
    shipDeceleration = 1200; // in pixels per second^2

    // bullet settings
    bulletWidth = 3;
    bulletHeight = 12;
    bulletColor = sf::Color::White;
    bulletMaxCount = 5;

    // alien settings
    fleetDropSpeed = 10;

    // how quickly the game speeds up
    speedUpScale = 1.1f;

    // how quickly the alien point values increase
    scoreScale = 1.5f;

    initializeDynamicSettings();
}

void Settings::initializeDynamicSettings()
{
    // initialize the settings that change during the game
    bulletSpeed = 500; // in pixels per second
    alienSpeed = 100; // in pixels per second

    // 1 represents right, -1 represents left
    fleetDirection = 1;

    // scoring
    alienPoints = 10;
}

// #include <iostream>
void Settings::increaseSpeed()
{
    bulletSpeed *= speedUpScale;
    alienSpeed *= speedUpScale;
    if (alienSpeed > 700)
    {
        alienSpeed = 700;
        fleetDropSpeed *= speedUpScale;
    }
    // std::cout << "bulletSpeed: " << bulletSpeed << std::endl;
    // std::cout << "alienSpeed: " << alienSpeed << std::endl;
    // std::cout << "fleetDropSpeed: " << fleetDropSpeed << std::endl;

    alienPoints = static_cast<unsigned int>(alienPoints * scoreScale);
}
