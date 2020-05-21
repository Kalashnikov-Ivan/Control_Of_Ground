#include "stdHeader.hpp"

#include "Game.hpp"

int main(int argc, char* argv[])
{   
	cog::Game game{ sf::VideoMode(800U, 600U) };

    game.run();

    return 0;
}