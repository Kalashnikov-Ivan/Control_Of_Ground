#include "stdHeader.hpp"

#include "State.hpp"

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
State::State(sf::RenderWindow* window,
	std::map<const std::string, int>* supported_keys, std::stack<State*>* states)
	: m_window(window), m_supported_keys(supported_keys), m_states(states),
	  m_quit(false)
{

}
State::~State()
{
	delete_textures();
}

//Support_cleaner
void State::delete_textures()
{
	for (auto& i : m_textures)
		delete i.second;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"])))
	{
		m_quit = true;
	}
}

void State::update_mouse_pos()
{
	m_mouse_pos_screen = sf::Mouse::getPosition();
	m_mouse_pos_window = sf::Mouse::getPosition(*m_window);
	m_mouse_pos_view = m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window));
}

sf::Text State::get_mouse_pos_text(const sf::Font& font) const
{
	std::stringstream ss; 
	ss << "x: " << m_mouse_pos_view.x << " " << "y: " << m_mouse_pos_view.y << std::endl;
	
	sf::Text mouse_text{ ss.str(), font, 12U };
	mouse_text.setPosition(m_mouse_pos_view.x + 10.f, m_mouse_pos_view.y - 10.f);

	return mouse_text;
}