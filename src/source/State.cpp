#include "stdHeader.hpp"

#include "State.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
State::State(sf::RenderWindow* window, std::map<const std::string, int>* supported_keys) :
	m_window(window), m_quit(false),
	m_supported_keys(supported_keys)
{

}
State::~State()
{

}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
const bool State::get_quit() const
{
	return m_quit;
}

void State::check_for_quit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_quit = true;
	}
}