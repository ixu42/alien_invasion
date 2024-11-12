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

        // getters
        sf::RenderWindow& getWindow() { return _window; }
        ResourceManager& getResourceManager() { return _resourceManager; }
        Settings& getSettings() { return _settings; }
        GameStats& getStats() { return _stats; }
        Ship& getShip() { return *_ship; }
        float getDeltaTime() { return _deltaTime; }

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

        sf::RenderWindow                    _window;
        ResourceManager                     _resourceManager;
        Settings                            _settings;
        GameStats                           _stats;
        sf::Clock                           _clock;
        float                               _deltaTime;
        std::unique_ptr<PlayButton>         _playButton;
        std::unique_ptr<Scoreboard>         _scoreboard;
        std::unique_ptr<Ship>               _ship;
        std::vector<Bullet>                 _bullets;
        std::vector<std::unique_ptr<Alien>> _aliens;
};
