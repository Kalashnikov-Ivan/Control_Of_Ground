#include "stdHeader.hpp"

#include "Game.hpp"

int main(int argc, char* argv[])
{   
    //_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);

	Core::Game game;

    game.run();

    return 0;
}