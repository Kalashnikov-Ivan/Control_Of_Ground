#include "stdafx.h"

#include "Game.hpp"

int main(int argc, char* argv[])
{   
    try
    {
        Core::Game game;

        game.Run();
    }
    catch (std::runtime_error& exception)
    {
        std::cerr << "Error: " << exception.what() << std::endl;
    }
    catch (std::exception& exception)
    {
        std::cerr << "Error: " << exception.what() << std::endl;
    }
    catch (...)
    {
        std::cerr << "Some exception..." << std::endl;
    }

    return 0;
}