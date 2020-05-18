#include "stdHeader.hpp"

#include "Entity.hpp"

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

	m_player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	m_player.render(target);
}

void GameState::end_state()
{
	std::cout << "State: Ending GameState..." << std::endl;
}