#include "Ship.hpp"

Ship::Ship(AlienInvasion* game)
    : movingLeft(false), movingRight(false), _game(game), _velocity(0, 0),
        _settings(game->getSettings())
{
    sprite.setTexture(_game->getResourceManager().getTexture("ship"));
    centerShip();
}

void Ship::update()
{
    applyAcceleration();
    applyDeceleration();

    // cap the ship's speed
    if (std::abs(_velocity.x) > _game->getSettings().shipMaxSpeed)
        _velocity.x = (_velocity.x > 0 ? 1 : -1) * _game->getSettings().shipMaxSpeed;

    // move the ship by the calculated velocity
    sprite.move(_velocity * _game->getDeltaTime());

    // keep the ship on the screen
    if (sprite.getPosition().x < 0)
        sprite.setPosition(0, sprite.getPosition().y);
    else if (sprite.getPosition().x + 
                sprite.getGlobalBounds().width > _game->getSettings().screenWidth)
        sprite.setPosition(_settings.screenWidth - 
                            sprite.getGlobalBounds().width, sprite.getPosition().y);
}

void Ship::applyAcceleration()
{
    if (movingLeft)
        _velocity.x -= _settings.shipAcceleration * _game->getDeltaTime();
    else if (movingRight)
        _velocity.x += _settings.shipAcceleration * _game->getDeltaTime();
}

void Ship::applyDeceleration()
{
    if (!movingLeft && !movingRight)
    {
        if (_velocity.x > 0)
        {
            _velocity.x -= _settings.shipDeceleration * _game->getDeltaTime();
            if (_velocity.x < 0)
                _velocity.x = 0;
        }
        else if (_velocity.x < 0)
        {
            _velocity.x += _settings.shipDeceleration * _game->getDeltaTime();
            if (_velocity.x > 0)
                _velocity.x = 0;
        }
    }
}

void Ship::render() const
{
    _game->getWindow().draw(sprite);
}

void Ship::centerShip()
{
    float xPos = (_settings.screenWidth - sprite.getGlobalBounds().width) / 2;
    float yPos = _settings.screenHeight - sprite.getGlobalBounds().height;
    sprite.setPosition(sf::Vector2f(xPos, yPos));
}
