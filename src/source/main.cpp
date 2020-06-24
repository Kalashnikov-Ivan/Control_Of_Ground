#include "stdHeader.hpp"

#include "Game.hpp"

int main(int argc, char* argv[])
{   
    //_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

    try
    {
        Core::Game game;

        game.run();
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