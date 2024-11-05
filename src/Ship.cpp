#include "Ship.hpp"

Ship::Ship(AlienInvasion* game) : movingLeft(false), movingRight(false), _game(game)
{
    sprite.setTexture(_game->shipTexture);
    sprite.setPosition(sf::Vector2f((_game->window.getSize().x - sprite.getGlobalBounds().width) / 2, _game->window.getSize().y - sprite.getGlobalBounds().height));
}

void Ship::update()
{
    if (movingLeft)
    {
        if (sprite.getPosition().x > 0)
            sprite.move(-_game->settings.shipSpeed, 0);
    }
    if (movingRight)
    {
        if (sprite.getPosition().x + sprite.getGlobalBounds().width < _game->window.getSize().x)
            sprite.move(_game->settings.shipSpeed, 0);
    }
}

void Ship::render()
{
    _game->window.draw(sprite);
}