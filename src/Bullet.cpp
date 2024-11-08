#include "Bullet.hpp"

Bullet::Bullet(AlienInvasion* game) : _game(game)
{
    auto shipMidtopX = _game->ship->sprite.getPosition().x 
                        + _game->ship->sprite.getGlobalBounds().width / 2;
    auto shipMidtopY = _game->ship->sprite.getPosition().y;
    setPosition(shipMidtopX, shipMidtopY);
    setFillColor(_game->settings.bulletColor);
    setSize(sf::Vector2f(_game->settings.bulletWidth, _game->settings.bulletHeight));
}

Bullet::Bullet(const Bullet& other) : _game(other._game)
{
    setPosition(other.getPosition());
    setFillColor(_game->settings.bulletColor);
    setSize(sf::Vector2f(_game->settings.bulletWidth, _game->settings.bulletHeight));
}

void Bullet::update()
{
    // move the bullet up
    this->move(0, -_game->settings.bulletSpeed);
}

void Bullet::draw() const
{
    _game->window.draw(*this);
}
