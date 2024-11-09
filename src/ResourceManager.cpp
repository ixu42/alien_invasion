#include "ResourceManager.hpp"

ResourceManager::ResourceManager()
{
    // load textures
    sf::Texture shipTexture;
    sf::Texture alienTexture;
    if (!shipTexture.loadFromFile("assets/images/ship.png"))
        throw std::runtime_error("Failed to load ship texture");
    if (!alienTexture.loadFromFile("assets/images/alien.png"))
        throw std::runtime_error("Failed to load alien texture");
    _textures["ship"] = std::move(shipTexture);
    _textures["alien"] = std::move(alienTexture);

    // load fonts
    sf::Font font;
    if (!font.loadFromFile("assets/fonts/audiowide.ttf"))
        throw std::runtime_error("Failed to load audiowide font");
    _fonts["audiowide"] = std::move(font);
}

sf::Texture& ResourceManager::getTexture(const std::string& textureName)
{
    auto it = _textures.find(textureName);
    if (it == _textures.end())
        throw std::runtime_error("Failed to find texture: " + textureName);
    return _textures[textureName];
}

sf::Font& ResourceManager::getFont(const std::string& fontName)
{
    auto it = _fonts.find(fontName);
    if (it == _fonts.end())
        throw std::runtime_error("Failed to find font: " + fontName);
    return _fonts[fontName];
}
