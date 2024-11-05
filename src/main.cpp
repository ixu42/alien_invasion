#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    unsigned int windowWidth = 1200u;
    unsigned int windowHeight = 800u;
    auto window = sf::RenderWindow({windowWidth, windowHeight}, "Alien Invasion");
    window.setFramerateLimit(144);

    sf::Texture texture;
    if (!texture.loadFromFile("src/ship.png"))
    {
        std::cout << "Error loading texture\n";
        return 1;
    }

    sf::Vector2u textureSize = texture.getSize();
    unsigned int shipWidth = textureSize.x;
    unsigned int shipHeight = textureSize.y;

    sf::Sprite ship(texture);
    ship.setPosition(sf::Vector2f((windowWidth - shipWidth ) / 2, windowHeight - shipHeight));

    while (window.isOpen())
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
            }
        }

        window.clear(sf::Color::Black);
        window.draw(ship);
        window.display();
    }
}
