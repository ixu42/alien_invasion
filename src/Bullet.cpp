#include "Bullet.hpp"

Bullet::Bullet(AlienInvasion* game) : _game(game)
{
    auto shipMidtopX = _game->getShip().sprite.getPosition().x 
                        + _game->getShip().sprite.getGlobalBounds().width / 2;
    auto shipMidtopY = _game->getShip().sprite.getPosition().y;
    setPosition(shipMidtopX, shipMidtopY);
    setFillColor(_game->getSettings().bulletColor);
    setSize(sf::Vector2f(_game->getSettings().bulletWidth, _game->getSettings().bulletHeight));
}

Bullet::Bullet(const Bullet& other) : _game(other._game)
{
    setPosition(other.getPosition());
    setFillColor(_game->getSettings().bulletColor);
    setSize(sf::Vector2f(_game->getSettings().bulletWidth, _game->getSettings().bulletHeight));
}

void Bullet::update()
{
    // move the bullet up
    this->move(0, -_game->getSettings().bulletSpeed * _game->getDeltaTime());
}

void Bullet::draw() const
{
    _game->getWindow().draw(*this);
}
