#include "Alien.hpp"

Alien::Alien(AlienInvasion* game)
{
    _game = game;

    if (!_alienTexture.loadFromFile("assets/alien.png"))
        throw std::runtime_error("Error loading texture");
    this->setTexture(_alienTexture);

    this->setPosition(0, 0);
}

void Alien::update()
{
    this->move(0.1, 0);
}

void Alien::render() const
{
    _game->window.draw(*this);
}
