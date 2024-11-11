#include "Ship.hpp"

Ship::Ship(AlienInvasion* game)
    : movingLeft(false), movingRight(false), _game(game), _velocity(0, 0)
{
    sprite.setTexture(_game->resourceManager.getTexture("ship"));
    centerShip();
}

void Ship::update()
{
    applyAcceleration();
    applyDeceleration();

    // cap the ship's speed
    if (std::abs(_velocity.x) > _game->settings.shipMaxSpeed)
        _velocity.x = (_velocity.x > 0 ? 1 : -1) * _game->settings.shipMaxSpeed;

    // move the ship by the calculated velocity
    sprite.move(_velocity * _game->deltaTime);

    // keep the ship on the screen
    if (sprite.getPosition().x < 0)
        sprite.setPosition(0, sprite.getPosition().y);
    else if (sprite.getPosition().x + sprite.getGlobalBounds().width > _game->settings.screenWidth)
        sprite.setPosition(_game->settings.screenWidth - sprite.getGlobalBounds().width, sprite.getPosition().y);
}

void Ship::applyAcceleration()
{
    if (movingLeft)
        _velocity.x -= _game->settings.shipAcceleration * _game->deltaTime;
    else if (movingRight)
        _velocity.x += _game->settings.shipAcceleration * _game->deltaTime;
}

void Ship::applyDeceleration()
{
    if (!movingLeft && !movingRight)
    {
        if (_velocity.x > 0)
        {
            _velocity.x -= _game->settings.shipDeceleration * _game->deltaTime;
            if (_velocity.x < 0)
                _velocity.x = 0;
        }
        else if (_velocity.x < 0)
        {
            _velocity.x += _game->settings.shipDeceleration * _game->deltaTime;
            if (_velocity.x > 0)
                _velocity.x = 0;
        }
    }
}

void Ship::render() const
{
    _game->window.draw(sprite);
}

void Ship::centerShip()
{
    float xPos = (_game->settings.screenWidth - sprite.getGlobalBounds().width) / 2;
    float yPos = _game->settings.screenHeight - sprite.getGlobalBounds().height;
    sprite.setPosition(sf::Vector2f(xPos, yPos));
}
