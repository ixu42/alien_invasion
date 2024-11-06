#include "Settings.hpp"

Settings::Settings()
    : screenWidth(1200),
      screenHeight(800),
      bgColor(sf::Color::Black),
      shipSpeed(10),
      bulletSpeed(5),
      bulletWidth(3),
      bulletHeight(12),
      bulletColor(sf::Color::White),
      bulletMaxCount(5),
      alienSpeed(1),
      fleetDropSpeed(10),
      fleetDirection(1) // 1 represents right, -1 represents left
{
}
