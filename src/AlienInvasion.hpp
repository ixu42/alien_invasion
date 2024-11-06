#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Settings.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Alien.hpp"

class Ship;
class Bullet;
class Alien;

class AlienInvasion
{
    public:
        AlienInvasion();
        void run();

        sf::RenderWindow window;
        Settings settings;
        std::unique_ptr<Ship> ship;
        std::unique_ptr<Alien> alien;
        std::vector<Bullet> bullets;

    private:
        void processEvents();
        void update();
        void render();
        void fireBullet();
        void updateBullets();
};
