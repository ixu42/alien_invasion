#include "Alien.hpp"

Alien::Alien(AlienInvasion* game) : _game(game)
{
    this->setTexture(_game->getResourceManager().getTexture("alien"));
    this->setPosition(this->getGlobalBounds().width, this->getGlobalBounds().height);
}

Alien::Alien(const Alien& other) : _game(other._game)
{
    this->setTexture(_game->getResourceManager().getTexture("alien"));
    this->setPosition(other.getGlobalBounds().width, other.getGlobalBounds().height);
}

void Alien::update()
{
    float movement = _game->getSettings().alienSpeed * 
                        _game->getSettings().fleetDirection * _game->getDeltaTime();
    this->move(movement, 0);
}

void Alien::render() const
{
    _game->getWindow().draw(*this);
}
