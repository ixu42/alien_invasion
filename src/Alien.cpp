#include "Alien.hpp"

Alien::Alien(AlienInvasion* game) : _game(game)
{
    this->setTexture(_game->resourceManager.getTexture("alien"));
    this->setPosition(this->getGlobalBounds().width, this->getGlobalBounds().height);
}

Alien::Alien(const Alien& other) : _game(other._game)
{
    this->setTexture(_game->resourceManager.getTexture("alien"));
    this->setPosition(other.getGlobalBounds().width, other.getGlobalBounds().height);
}

void Alien::update()
{
    float movement = _game->settings.alienSpeed * _game->settings.fleetDirection * _game->deltaTime;
    this->move(movement, 0);
}

void Alien::render() const
{
    _game->window.draw(*this);
}
