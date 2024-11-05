#pragma once

#include <SFML/Graphics.hpp>
#include "AlienInvasion.hpp"

class AlienInvasion;

class Ship
{
    public:
        Ship(AlienInvasion* game);
        void update();
        void render();

        sf::Sprite sprite;
        bool movingLeft;
        bool movingRight;

    private:
        AlienInvasion* _game;
};