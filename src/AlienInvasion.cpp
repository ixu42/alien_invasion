#include "AlienInvasion.hpp"

AlienInvasion::AlienInvasion() 
    : settings(Settings()), stats(GameStats(this)), playButton(PlayButton(this))
{
    window.create({settings.screenWidth, settings.screenHeight}, "Alien Invasion");
    window.setFramerateLimit(144);

    if (!alienTexture.loadFromFile("assets/images/alien.png"))
        throw std::runtime_error("Failed to load alien texture");

    ship = std::make_unique<Ship>(this);
    create_fleet();
}

void AlienInvasion::run()
{
    while (window.isOpen())
    {
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
    
    // check for collisions between aliens and the ship
    for (auto& alien : aliens)
    {
        if (alien->getGlobalBounds().intersects(ship->sprite.getGlobalBounds()))
        {
            std::cout << "Ship hit by alien\n";
            shipHit();
            break ;
        }
    }
}

void AlienInvasion::render()
{
    window.clear(settings.bgColor);
    ship->render();
    for (Bullet& bullet : bullets)
        bullet.draw();
    for (auto& alien : aliens)
        alien->render();
    if (!stats.gameActive)
        playButton.draw();
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

    checkBulletAlienCollisions();
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

void AlienInvasion::checkBulletAlienCollisions()
{
    for (auto bulletIter = bullets.begin(); bulletIter != bullets.end();)
    {
        bool collided = false;
        for (auto alienIter = aliens.begin(); alienIter != aliens.end();)
        {
            if (bulletIter->getGlobalBounds().intersects((*alienIter)->getGlobalBounds()))
            {
                alienIter = aliens.erase(alienIter);
                if (!collided)
                    collided = true;
            }
            else
                ++alienIter;
        }
        if (collided)
            bulletIter = bullets.erase(bulletIter);
        else
            ++bulletIter;
    }

    // if the fleet is destroyed, destroy existing bullets and create a new fleet
    if (aliens.empty())
    {
        bullets.clear();
        create_fleet();
    }
}

void AlienInvasion::shipHit()
{
    if (stats.shipsLeft > 0)
    {
        // decrement shipsLeft
        stats.shipsLeft -= 1;
        std::cout << "ships left: " << stats.shipsLeft << std::endl;

        // get rid of remaining aliens and bullets
        aliens.clear();
        bullets.clear();

        // create a new fleet and center the ship
        create_fleet();
        ship->centerShip();

        // pause
        sf::sleep(sf::seconds(0.5));
    }
    else
    {
        stats.gameActive = false;
        std::cout << "Game over\n";
    }
}
