#include "stdHeader.hpp"

#include "State.hpp"
#include "GameState.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
GameState::GameState(sf::RenderWindow* window)
	: State(window)
{

}

GameState::~GameState()
{
}

////////////////////////////////////////////////////////////
// Virtual override
////////////////////////////////////////////////////////////
void GameState::update_key_binds(const float& dt)
{
	check_for_quit();
}

void GameState::update(const float& dt)
{
	update_key_binds(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		std::cout << 'A' << '\n';
}

void GameState::render(sf::RenderTarget* target)
{

}

void GameState::end_state()
{
	std::cout << "State: Ending GameState..." << std::endl;
}