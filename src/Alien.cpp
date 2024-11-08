#include "Alien.hpp"

Alien::Alien(AlienInvasion* game) : _game(game)
{
    if (!_alienTexture.loadFromFile("assets/images/alien.png"))
        throw std::runtime_error("Failed to load alien texture");
    this->setTexture(_alienTexture);
    this->setPosition(this->getGlobalBounds().width, this->getGlobalBounds().height);
}

Alien::Alien(const Alien& other) : _game(other._game)
{
    this->setTexture(_alienTexture);
    this->setPosition(other.getGlobalBounds().width, other.getGlobalBounds().height);
}

void Alien::update()
{
    this->move(_game->settings.alienSpeed * _game->settings.fleetDirection, 0);
}

void Alien::render() const
{
    _game->window.draw(*this);
}

bool Alien::reachedEdge() const
{
    if (this->getPosition().x <= 0
        || this->getPosition().x >= _game->settings.screenWidth - this->getGlobalBounds().width)
        return true;
    return false;
}
