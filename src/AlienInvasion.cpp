#include "AlienInvasion.hpp"

AlienInvasion::AlienInvasion() : settings(Settings())
{
    window.create({settings.screenWidth, settings.screenHeight}, "Alien Invasion");
    window.setFramerateLimit(144);

    if (!shipTexture.loadFromFile("assets/ship.png"))
        std::cout << "Error loading texture\n";

    _ship = std::make_unique<Ship>(this);
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
                _ship->movingLeft = true;
            if (event.key.code == sf::Keyboard::Right)
                _ship->movingRight = true;
        }
        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Left)
                _ship->movingLeft = false;
            if (event.key.code == sf::Keyboard::Right)
                _ship->movingRight = false;
        }
    }
}

void AlienInvasion::update()
{
    _ship->update();
}

void AlienInvasion::render()
{
    window.clear(settings.bgColor);
    _ship->render();
    window.display();
}
