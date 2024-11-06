#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "Settings.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"

class Ship;
class Bullet;

class AlienInvasion
{
    public:
        AlienInvasion();
        void run();

        sf::RenderWindow window;
        sf::Texture shipTexture;
        Settings settings;
        std::unique_ptr<Ship> ship;
        std::vector<Bullet> bullets;

    private:
        void processEvents();
        void update();
        void render();
        void fireBullet();
        void updateBullets();
};
