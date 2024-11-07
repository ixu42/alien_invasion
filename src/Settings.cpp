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
}
#include <iostream>
void Settings::increaseSpeed()
{
    std::cout << "Speeding up\n";
    std::cout << "Ship speed: " << shipSpeed << std::endl;
    std::cout << "Bullet speed: " << bulletSpeed << std::endl;
    std::cout << "Alien speed: " << alienSpeed << std::endl;
    shipSpeed *= speedUpScale;
    bulletSpeed *= speedUpScale;
    alienSpeed *= speedUpScale;
    if (alienSpeed > 4)
    alienSpeed = 4;
    std::cout << "Ship speed after: " << shipSpeed << std::endl;
    std::cout << "Bullet speed after: " << bulletSpeed << std::endl;
    std::cout << "Alien speed after: " << alienSpeed << std::endl;
}