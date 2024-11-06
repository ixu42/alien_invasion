#pragma once

#include <SFML/Graphics.hpp>
#include "AlienInvasion.hpp"
#include <stdexcept>

class AlienInvasion;

class Alien : sf::Sprite
{
    public:
        Alien(AlienInvasion* game);
        void update();
        void render() const;
    
    private:
        AlienInvasion*  _game;
        sf::Texture     _alienTexture;
};
