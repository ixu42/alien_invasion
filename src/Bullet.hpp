#pragma once

#include <SFML/Graphics.hpp>
#include "AlienInvasion.hpp"

class AlienInvasion;

class Bullet : public sf::RectangleShape
{
    public:
        Bullet(AlienInvasion* game);
        Bullet(const Bullet& other);
        void update();
        void draw() const;

    private:
        AlienInvasion* _game;
};
