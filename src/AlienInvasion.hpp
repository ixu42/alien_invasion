#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include <utility>
#include "ResourceManager.hpp" 
#include "Settings.hpp"
#include "GameStats.hpp"
#include "Scoreboard.hpp"
#include "Ship.hpp"
#include "Bullet.hpp"
#include "Alien.hpp"
#include "PlayButton.hpp"

class Ship;
class Bullet;
class Alien;

class AlienInvasion
{
    public:
        AlienInvasion();
        void run();

        sf::RenderWindow        window;
        ResourceManager         resourceManager;
        Settings                settings;
        GameStats               stats;
        std::unique_ptr<Ship>   ship;
        float                   deltaTime;

    private:
        // main game loop functions
        void processEvents();
        void update();
        void render();

        // helper functions for processEvents() and constructor
        void startGame();
        void createFleet();
        void fireBullet();

        // update bullets and check for collisions between bullets and aliens
        void updateBullets();
        void checkBulletAlienCollisions();
        void startNewLevel();

        // update aliens and check for collisions between aliens and ship/bottom of screen
        void updateAliens();
        void checkFleetEdges();
        void changeFleetDirection();
        void checkFleetBottom();
        void shipHit();

        std::vector<Bullet>                 _bullets;
        std::vector<std::unique_ptr<Alien>> _aliens;
        std::unique_ptr<PlayButton>         _playButton;
        std::unique_ptr<Scoreboard>         _scoreboard;
        sf::Clock                           _clock;
};
