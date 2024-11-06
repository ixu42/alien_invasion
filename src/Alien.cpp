#include "Alien.hpp"

Alien::Alien(AlienInvasion* game) : _game(game)
{
    this->setTexture(_game->alienTexture);
    this->setPosition(this->getGlobalBounds().width, this->getGlobalBounds().height);
}

Alien::Alien(const Alien& other) : _game(other._game)
{
    this->setTexture(_game->alienTexture);
    this->setPosition(other.getGlobalBounds().width, other.getGlobalBounds().height);
}

void Alien::update()
{
    // this->move(0.1, 0);
}

void Alien::render() const
{
    _game->window.draw(*this);
}
