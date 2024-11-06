#include "AlienInvasion.hpp"
#include <iostream>
#include <exception>

int main()
{
    try
    {
        AlienInvasion game;
        game.run();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
