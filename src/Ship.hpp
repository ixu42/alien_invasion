#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include "AlienInvasion.hpp"

class AlienInvasion;

class Ship
{
    public:
        Ship(AlienInvasion* game);
        void update();
        void render() const;
        void centerShip();

        sf::Sprite      sprite;
        bool            movingLeft;
        bool            movingRight;

    private:
        void applyAcceleration();
        void applyDeceleration();

        AlienInvasion*  _game;
        sf::Vector2f    _velocity;
};
