#include "stdHeader.hpp"

#include "MainMenuState.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<const std::string, int>* supported_keys) :
	State(window, supported_keys)
{
}

MainMenuState::~MainMenuState()
{
}

////////////////////////////////////////////////////////////
// Virtual override
////////////////////////////////////////////////////////////
void MainMenuState::update_input(const float& dt)
{

}

void MainMenuState::update(const float& dt)
{

}

void MainMenuState::render(sf::RenderTarget* target)
{

}

void MainMenuState::end_state()
{

}