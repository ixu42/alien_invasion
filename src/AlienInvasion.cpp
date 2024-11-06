#include "AlienInvasion.hpp"

AlienInvasion::AlienInvasion() : settings(Settings())
{
    window.create({settings.screenWidth, settings.screenHeight}, "Alien Invasion");
    window.setFramerateLimit(144);

    ship = std::make_unique<Ship>(this);
    alien = std::make_unique<Alien>(this);
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
    alien->update();
}

void AlienInvasion::render()
{
    window.clear(settings.bgColor);
    ship->render();
    for (Bullet& bullet : bullets)
        bullet.draw();
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
