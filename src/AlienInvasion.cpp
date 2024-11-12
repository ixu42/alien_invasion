#include "AlienInvasion.hpp"

AlienInvasion::AlienInvasion() 
    : _settings(Settings()), _stats(GameStats(this))
{
    _window.create({_settings.screenWidth, _settings.screenHeight}, "Alien Invasion");
    _window.setFramerateLimit(60);

    // initialize ui components
    _playButton = std::make_unique<PlayButton>(this);
    _scoreboard = std::make_unique<Scoreboard>(this);

    // initialize game objects
    _ship = std::make_unique<Ship>(this);
    createFleet();
}

void AlienInvasion::run()
{
    while (_window.isOpen())
    {
        _deltaTime = _clock.restart().asSeconds();
        if (_deltaTime > 0.017f)
            _deltaTime = 0.017f;
        processEvents();
        if (_stats.isGameActive())
            update();
        render();
    }
}

void AlienInvasion::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            _window.close();        
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                _window.close();
            else if (event.key.code == sf::Keyboard::P)
                startGame();
            else if (event.key.code == sf::Keyboard::Left)
                _ship->movingLeft = true;
            else if (event.key.code == sf::Keyboard::Right)
                _ship->movingRight = true;
            else if (event.key.code == sf::Keyboard::Space && _stats.isGameActive())
                    fireBullet();
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Left)
                _ship->movingLeft = false;
            else if (event.key.code == sf::Keyboard::Right)
                _ship->movingRight = false;
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(_window);
            sf::Vector2f worldPos = _window.mapPixelToCoords(pixelPos);
            if (_playButton->getButton().getGlobalBounds().contains(worldPos.x, worldPos.y))
                startGame();
        }
    }
}

void AlienInvasion::update()
{
    _ship->update();
    updateBullets();
    updateAliens();
}

void AlienInvasion::render()
{
    _window.clear(_settings.bgColor);
    _ship->render();
    for (Bullet& bullet : _bullets)
        bullet.draw();
    for (auto& alien : _aliens)
        alien->render();
    _scoreboard->draw();
    if (!_stats.isGameActive())
        _playButton->draw();
    _window.display();
}

void AlienInvasion::startGame()
{
    if (!_stats.isGameActive())
    {
        _settings.initializeDynamicSettings();
        _stats.resetStats();
        _stats.setGameActive(true);
        _aliens.clear();
        _bullets.clear();
        createFleet();
        _ship->centerShip();
        _window.setMouseCursorVisible(false);
        _scoreboard->updateScore();
        _scoreboard->updateLevel();
        _scoreboard->updateShipsLeft();
    }
}

void AlienInvasion::createFleet()
{
    // create an alien and find the number of aliens that fit in a row
    Alien tempAlien(this);
    float alienWidth = tempAlien.getGlobalBounds().width;
    float alienHeight = tempAlien.getGlobalBounds().height;
    float avalableSpaceX = _settings.screenWidth - 2 * alienWidth;
    unsigned int numberOfAliensX = avalableSpaceX / (2 * alienWidth);

    // determine the number of rows of aliens that fit on the screen
    float shipHeight = _ship->sprite.getGlobalBounds().height;
    float availableSpaceY = _settings.screenHeight - 6 * alienHeight - shipHeight;
    unsigned int numberOfAliensY = availableSpaceY / (3 * alienHeight);

    // create full fleet of aliens
    for (int i = 0; i < numberOfAliensX; ++i)
    {
        for (int j = 0; j < numberOfAliensY; ++j)
        {
            auto newAlien = std::make_unique<Alien>(this);
            newAlien->setPosition(alienWidth + 2 * alienWidth * i, alienHeight + 3 * alienHeight * j);
            _aliens.push_back(std::move(newAlien));
        }
    }
}

void AlienInvasion::fireBullet()
{
    if (_bullets.size() >= _settings.bulletMaxCount)
        return;
    Bullet newBullet(this);
    _bullets.push_back(newBullet);
}

void AlienInvasion::updateBullets()
{
    for (Bullet& bullet : _bullets)
        bullet.update();

    // get rid of bullets that have gone off screen
    for (auto it = _bullets.begin(); it != _bullets.end();)
    {
        if (it->getPosition().y + it->getSize().y <= 0)
            it = _bullets.erase(it);
        else
            ++it;
    }

    checkBulletAlienCollisions();
}

void AlienInvasion::checkBulletAlienCollisions()
{
    for (auto bulletIter = _bullets.begin(); bulletIter != _bullets.end();)
    {
        bool collided = false;
        for (auto alienIter = _aliens.begin(); alienIter != _aliens.end();)
        {
            if (bulletIter->getGlobalBounds().intersects((*alienIter)->getGlobalBounds()))
            {
                alienIter = _aliens.erase(alienIter);
                if (!collided)
                    collided = true;
                _stats.addScore(_settings.alienPoints);
                _scoreboard->updateScore();
                _scoreboard->checkHighScore();
            }
            else
                ++alienIter;
        }
        if (collided)
            bulletIter = _bullets.erase(bulletIter);
        else
            ++bulletIter;
    }

    // if the fleet is destroyed, destroy existing bullets and create a new fleet
    if (_aliens.empty())
        startNewLevel();
}

void AlienInvasion::startNewLevel()
{
    _bullets.clear();
    createFleet();
    _settings.increaseSpeed();
    _stats.incrementLevel();
    _scoreboard->updateLevel();
}

void AlienInvasion::updateAliens()
{
    checkFleetEdges();

    for (auto& alien : _aliens)
        alien->update();
    
    // check for collisions between aliens and the ship
    for (auto& alien : _aliens)
    {
        if (alien->getGlobalBounds().intersects(_ship->sprite.getGlobalBounds()))
        {
            shipHit();
            break ;
        }
    }

    checkFleetBottom();
}

void AlienInvasion::checkFleetEdges()
{
    // std::cout << "_deltaTime: " << _deltaTime << std::endl;
    for (unsigned int i = 0; i < _aliens.size(); ++i)
    {
        float nextPositionX = _aliens[i]->getPosition().x + _settings.alienSpeed * _settings.fleetDirection * _deltaTime;
        if (nextPositionX <= 0 || nextPositionX >= _settings.screenWidth - _aliens[i]->getGlobalBounds().width)
        {
            changeFleetDirection();
            break;
        }
    }
}

void AlienInvasion::changeFleetDirection()
{
    _settings.fleetDirection *= -1;
    for (auto& alien : _aliens)
        alien->move(0, _settings.fleetDropSpeed);
}

void AlienInvasion::checkFleetBottom()
{
    for (auto& alien : _aliens)
    {
        if (alien->getPosition().y + alien->getGlobalBounds().height >= _settings.screenHeight)
        {
            shipHit();
            break;
        }
    }
}

void AlienInvasion::shipHit()
{
    if (_stats.getShipsLeft() > 0)
    {
        // decrement shipsLeft and update scoreboard
        _stats.decrementShipsLeft();
        _scoreboard->updateShipsLeft();

        // get rid of remaining aliens and bullets
        _aliens.clear();
        _bullets.clear();

        // create a new fleet and center the ship
        createFleet();
        _ship->centerShip();

        // pause
        sf::sleep(sf::seconds(0.5));
    }
    else
    {
        _stats.setGameActive(false);
        _window.setMouseCursorVisible(true);
    }
}
