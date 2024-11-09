#pragma once

#include <SFML/Graphics.hpp>
#include "AlienInvasion.hpp"

class AlienInvasion;

class Alien : public sf::Sprite
{
    public:
        Alien(AlienInvasion* game);
        Alien(const Alien& other);
        void update();
        void render() const;
    
    private:
        AlienInvasion*  _game;
        sf::Texture     _alienTexture;
};
