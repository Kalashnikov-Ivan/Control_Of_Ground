#include "stdHeader.hpp"

#include "MainMenuState.hpp"

#define DEBUG

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<const std::string, int>* supported_keys) :
	State(window, supported_keys)
{
	init_keybinds();

	m_background.setSize(static_cast<sf::Vector2f>(m_window->getSize()));
	m_background.setFillColor(sf::Color::Magenta);
}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::init_keybinds()
{
#ifdef DEBUG
	std::cout << "\nMainMenuState: Start of init_keybinds..." << std::endl;
#endif // DEBUG

	std::ifstream keys_ifs("config/MainMenuState_keybinds.ini");
	if (keys_ifs.is_open())
	{
		std::string key{ "" };
		std::string key_value{ "" };

		while (keys_ifs >> key >> key_value)
		{
			m_keybinds[key] = m_supported_keys->at(key_value);
		}
	}
	else
	{
		std::cerr << "config/MainMenuState_keybinds.ini - cannot open!"
			<< std::endl
			<< "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_supported_keys->at("Escape");

		m_keybinds["MOVE_LEFT"] = m_supported_keys->at("A");
		m_keybinds["MOVE_RIGHT"] = m_supported_keys->at("D");
		m_keybinds["MOVE_TOP"] = m_supported_keys->at("W");
		m_keybinds["MOVE_DOWN"] = m_supported_keys->at("S");
	}

	keys_ifs.close();

#ifdef DEBUG
	for (auto& i : m_keybinds)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "\nMainMenuState: init_keybinds is success!" << std::endl;
#endif // DEBUG
}

////////////////////////////////////////////////////////////
// Virtual override
////////////////////////////////////////////////////////////
void MainMenuState::update_input(const float& dt)
{
	check_for_quit();

}

void MainMenuState::update(const float& dt)
{
	update_input(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(m_background);
}

void MainMenuState::end_state()
{
	std::cout << "MainMenuState: Ending..." << std::endl;
}