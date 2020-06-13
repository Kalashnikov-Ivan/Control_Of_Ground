#include "stdHeader.hpp"

#include "State.hpp"

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
State::State(StateData& Sdata)
	: m_Sdata		 { Sdata },
	m_quit           { false },
	m_paused         { false }
{
}
State::~State()
{
	deleteTextures();
	std::cout << "STATE DEAD";
}

//Support_cleaner
void State::deleteTextures()
{
	for (auto& i : m_textures)
		delete i.second;
}

////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////
const bool State::getQuit() const
{
	return m_quit;
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
std::string States::State::getStringMousePos() const
{
	std::stringstream result;

	result << "mouse x = " << m_mouse_pos_view.x << " " << "y = " << m_mouse_pos_view.y << '\n';

	return result.str();
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

void States::State::pause()
{
	m_paused = true;
}

void States::State::unpause()
{
	m_paused = false;
}

void State::reset()
{

}

void State::quitState()
{
	m_quit = true;
}

void State::updateMousePos()
{
	m_mouse_pos_screen = sf::Mouse::getPosition();
	m_mouse_pos_window = sf::Mouse::getPosition(m_Sdata.window);
	m_mouse_pos_view = m_Sdata.window.mapPixelToCoords(sf::Mouse::getPosition(m_Sdata.window));
}