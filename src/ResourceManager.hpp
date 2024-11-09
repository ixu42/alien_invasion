#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class ResourceManager
{
    public:
        ResourceManager();
        sf::Texture& getTexture(const std::string& filepath);
        sf::Font& getFont(const std::string& filepath);

    private:
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Font>    _fonts;
};
