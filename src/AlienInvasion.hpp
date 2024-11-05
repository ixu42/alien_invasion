#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Ship.hpp"

class Ship;

class AlienInvasion
{
    public:
        AlienInvasion();
        void run();

        sf::RenderWindow window;
        sf::Texture shipTexture;

    private:
        void processEvents();
        void update();
        void render();

        std::unique_ptr<Ship> _ship;
};
