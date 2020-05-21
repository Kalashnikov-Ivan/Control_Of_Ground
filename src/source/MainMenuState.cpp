#include "stdHeader.hpp"

#include "MainMenuState.hpp"

#define DEBUG

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(sf::RenderWindow* window, 
	std::map<const std::string, int>* supported_keys, std::stack<State*>* states) 
	: State{ window, supported_keys, states }
{
	init_fonts();
	init_buttons();
	init_keybinds();

	m_background.setSize(static_cast<sf::Vector2f>(m_window->getSize()));
	m_background.setFillColor(sf::Color::Black);
}

MainMenuState::~MainMenuState()
{
	delete_buttons();
}

//Support_cleaner
void MainMenuState::delete_buttons()
{
	for (auto& i : m_buttons)
		delete i.second;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void MainMenuState::init_fonts()
{
	if (!m_font.loadFromFile("resources/fonts/Dosis-Regular.ttf"))
		throw "ERROR::MainMenuState: init_fonts. Can't open font";
}

void MainMenuState::init_buttons()
{
	m_buttons["GAME_STATE"] = new Button{ sf::Vector2f(100, 100), sf::Vector2f(150, 85),
								&m_font, "New Game", 26U,
								sf::Color::Blue, sf::Color::Cyan, sf::Color::Green };

	m_buttons["EXIT_STATE"] = new Button{ sf::Vector2f(100, 200), sf::Vector2f(150, 85),
								&m_font, "Exit", 26U,
								sf::Color::Blue, sf::Color::Cyan, sf::Color::Green };

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

void MainMenuState::update_buttons(const float& dt)
{
	for (auto& i : m_buttons)
		i.second->update(m_mouse_pos_view);

	if (m_buttons["GAME_STATE"]->is_pressed())
		m_quit = true;
	
	if (m_buttons["EXIT_STATE"]->is_pressed())
		m_quit = true;
}

void MainMenuState::render_buttons(sf::RenderTarget* target)
{
	for (auto& i : m_buttons)
		i.second->render(target);
}

void MainMenuState::update(const float& dt)
{
	update_mouse_pos();
	print_mouse_pos();

	update_input(dt);
	update_buttons(dt);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;

	target->draw(m_background);
	render_buttons(target);
}

void MainMenuState::end_state()
{
	std::cout << "MainMenuState: Ending..." << std::endl;
}