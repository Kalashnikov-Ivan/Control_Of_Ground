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

void State::print_mouse_pos()
{
	//system("cls");
	std::cout << "Pos_view: " << m_mouse_pos_view.x << " " << m_mouse_pos_view.y << std::endl;
	std::cout << "Pos_window: " << m_mouse_pos_window.x << " " << m_mouse_pos_window.y << std::endl;
	std::cout << "Pos_screen: " << m_mouse_pos_screen.x << " " << m_mouse_pos_screen.y << "\r";
}