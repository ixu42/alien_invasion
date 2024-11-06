#include "AlienInvasion.hpp"

AlienInvasion::AlienInvasion() : settings(Settings())
{
    window.create({settings.screenWidth, settings.screenHeight}, "Alien Invasion");
    window.setFramerateLimit(144);

    if (!alienTexture.loadFromFile("assets/alien.png"))
        throw std::runtime_error("Failed to load alien texture");

    ship = std::make_unique<Ship>(this);
    create_fleet();
}

void AlienInvasion::run()
{
    while (window.isOpen())
    {
        processEvents();
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
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
                window.close();
            if (event.key.code == sf::Keyboard::Left)
                ship->movingLeft = true;
            if (event.key.code == sf::Keyboard::Right)
                ship->movingRight = true;
            if (event.key.code == sf::Keyboard::Space)
                fireBullet();
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Left)
                ship->movingLeft = false;
            if (event.key.code == sf::Keyboard::Right)
                ship->movingRight = false;
        }
    }
}

void AlienInvasion::update()
{
    ship->update();
    updateBullets();
    checkFleetEdges();
    for (auto& alien : aliens)
        alien->update();
}

void AlienInvasion::render()
{
    window.clear(settings.bgColor);
    ship->render();
    for (Bullet& bullet : bullets)
        bullet.draw();
    for (auto& alien : aliens)
        alien->render();
    window.display();
}

void AlienInvasion::fireBullet()
{
    if (bullets.size() >= settings.bulletMaxCount)
        return;
    Bullet newBullet(this);
    bullets.push_back(newBullet);
}

void AlienInvasion::updateBullets()
{
    for (Bullet& bullet : bullets)
        bullet.update();

    // get rid of bullets that have gone off screen
    for (auto it = bullets.begin(); it != bullets.end();)
    {
        if (it->getPosition().y + it->getSize().y <= 0)
            it = bullets.erase(it);
        else
            ++it;
    }
}

void AlienInvasion::create_fleet()
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
            aliens.push_back(std::move(newAlien));
        }
    }
}

void AlienInvasion::checkFleetEdges()
{
    for (auto& alien : aliens)
    {
        if (alien->reachedEdge())
        {
            changeFleetDirection();
            break;
        }
    }
}

void AlienInvasion::changeFleetDirection()
{
    settings.fleetDirection *= -1;
    for (auto& alien : aliens)
        alien->move(0, settings.fleetDropSpeed);
}
