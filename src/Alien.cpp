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
    float movement = _game->settings.alienSpeed * _game->settings.fleetDirection * _game->deltaTime;
    this->move(movement, 0);
}

void Alien::render() const
{
    _game->window.draw(*this);
}
