#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include <vector>
#include <utility>
#include "Settings.hpp"
#include "GameStats.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Alien.hpp"
#include "PlayButton.hpp"

class Ship;
class Bullet;
class Alien;
class PlayButton;

class AlienInvasion
{
    public:
        AlienInvasion();
        void run();

        sf::RenderWindow window;
        Settings settings;
        GameStats stats;
        PlayButton playButton;
        std::unique_ptr<Ship> ship;
        std::vector<Bullet> bullets;
        std::vector<std::unique_ptr<Alien>> aliens;
        
        sf::Texture alienTexture;

    private:
        void processEvents();
        void update();
        void render();

        void startGame();

        // helper functions for handling bullets
        void fireBullet();
        void updateBullets();

        // helper functions for handling aliens
        void createFleet();
        void checkFleetEdges();
        void checkFleetBottom();
        void changeFleetDirection();
        void updateAliens();

        void checkBulletAlienCollisions();

        void shipHit();
};
