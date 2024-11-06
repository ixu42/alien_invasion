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
        std::vector<Bullet> bullets;
        std::vector<std::unique_ptr<Alien>> aliens;
        
        sf::Texture alienTexture;

    private:
        void processEvents();
        void update();
        void render();

        // helper functions for handling bullets
        void fireBullet();
        void updateBullets();

        // create the fleet of aliens
        void create_fleet();
        void checkFleetEdges();
        void changeFleetDirection();
};
