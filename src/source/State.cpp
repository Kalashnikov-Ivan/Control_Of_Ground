#include "stdHeader.hpp"

#include "State.hpp"

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
State::State(sf::RenderWindow& window,
			 std::stack<State*>& states,
			 std::map<const std::string, sf::Font*>& supported_fonts,
			 const std::map<const std::string, int>& supported_keys)
	: m_window		 { window },
	m_states         { states },
	m_supported_fonts{ supported_fonts },
	m_supported_keys { supported_keys },
	m_quit           { false }
{
}
State::~State()
{
	deleteTextures();
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
// Tech info
////////////////////////////////////////////////////////////
sf::Text State::getMousePosText(const sf::Font& font) const
{
	std::stringstream ss;
	ss << "x: " << m_mouse_pos_view.x << " " << "y: " << m_mouse_pos_view.y;

	sf::Text mouse_text{ ss.str(), font, 12U };
	mouse_text.setPosition(m_mouse_pos_view.x + 10.f, m_mouse_pos_view.y - 10.f);

	return mouse_text;
}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////

void State::endState()
{
	m_quit = true;
}

void State::updateMousePos()
{
	m_mouse_pos_screen = sf::Mouse::getPosition();
	m_mouse_pos_window = sf::Mouse::getPosition(m_window);
	m_mouse_pos_view = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
}