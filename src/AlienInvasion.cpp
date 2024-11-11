#include "AlienInvasion.hpp"

AlienInvasion::AlienInvasion() 
    : settings(Settings()), stats(GameStats(this))
{
    window.create({settings.screenWidth, settings.screenHeight}, "Alien Invasion");
    window.setFramerateLimit(60);

    // initialize ui components
    _playButton = std::make_unique<PlayButton>(this);
    _scoreboard = std::make_unique<Scoreboard>(this);

    // initialize game objects
    ship = std::make_unique<Ship>(this);
    createFleet();
}

void AlienInvasion::run()
{
    while (window.isOpen())
    {
        deltaTime = _clock.restart().asSeconds();
        if (deltaTime > 0.017f)
            deltaTime = 0.017f;
        processEvents();
        if (stats.gameActive)
            update();
        render();
    }
}

void AlienInvasion::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();        
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            else if (event.key.code == sf::Keyboard::P)
                startGame();
            else if (event.key.code == sf::Keyboard::Left)
                ship->movingLeft = true;
            else if (event.key.code == sf::Keyboard::Right)
                ship->movingRight = true;
            else if (event.key.code == sf::Keyboard::Space && stats.gameActive)
                    fireBullet();
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Left)
                ship->movingLeft = false;
            else if (event.key.code == sf::Keyboard::Right)
                ship->movingRight = false;
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);
            if (_playButton->button.getGlobalBounds().contains(worldPos.x, worldPos.y))
                startGame();
        }
    }
}

void AlienInvasion::update()
{
    ship->update();
    updateBullets();
    updateAliens();
}

void AlienInvasion::render()
{
    window.clear(settings.bgColor);
    ship->render();
    for (Bullet& bullet : _bullets)
        bullet.draw();
    for (auto& alien : _aliens)
        alien->render();
    _scoreboard->draw();
    if (!stats.gameActive)
        _playButton->draw();
    window.display();
}

void AlienInvasion::startGame()
{
    if (!stats.gameActive)
    {
        settings.initializeDynamicSettings();
        stats.resetStats();
        stats.gameActive = true;
        _aliens.clear();
        _bullets.clear();
        createFleet();
        ship->centerShip();
        window.setMouseCursorVisible(false);
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
    float avalableSpaceX = settings.screenWidth - 2 * alienWidth;
    unsigned int numberOfAliensX = avalableSpaceX / (2 * alienWidth);

    // determine the number of rows of aliens that fit on the screen
    float shipHeight = ship->sprite.getGlobalBounds().height;
    float availableSpaceY = settings.screenHeight - 6 * alienHeight - shipHeight;
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
    if (_bullets.size() >= settings.bulletMaxCount)
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
                stats.score += settings.alienPoints;
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
    settings.increaseSpeed();
    stats.level += 1;
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
        if (alien->getGlobalBounds().intersects(ship->sprite.getGlobalBounds()))
        {
            shipHit();
            break ;
        }
    }

    checkFleetBottom();
}

void AlienInvasion::checkFleetEdges()
{
    // std::cout << "deltaTime: " << deltaTime << std::endl;
    for (unsigned int i = 0; i < _aliens.size(); ++i)
    {
        float nextPositionX = _aliens[i]->getPosition().x + settings.alienSpeed * settings.fleetDirection * deltaTime;
        if (nextPositionX <= 0 || nextPositionX >= settings.screenWidth - _aliens[i]->getGlobalBounds().width)
        {
            changeFleetDirection();
            break;
        }
    }
}

void AlienInvasion::changeFleetDirection()
{
    settings.fleetDirection *= -1;
    for (auto& alien : _aliens)
        alien->move(0, settings.fleetDropSpeed);
}

void AlienInvasion::checkFleetBottom()
{
    for (auto& alien : _aliens)
    {
        if (alien->getPosition().y + alien->getGlobalBounds().height >= settings.screenHeight)
        {
            shipHit();
            break;
        }
    }
}

void AlienInvasion::shipHit()
{
    if (stats.shipsLeft > 0)
    {
        // decrement shipsLeft and update scoreboard
        stats.shipsLeft -= 1;
        _scoreboard->updateShipsLeft();

        // get rid of remaining aliens and bullets
        _aliens.clear();
        _bullets.clear();

        // create a new fleet and center the ship
        createFleet();
        ship->centerShip();

        // pause
        sf::sleep(sf::seconds(0.5));
    }
    else
    {
        stats.gameActive = false;
        window.setMouseCursorVisible(true);
    }
}
