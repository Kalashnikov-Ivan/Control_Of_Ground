#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "EditorState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(sf::RenderWindow& window,
							 std::stack<State*>& states,
							 std::map<const std::string, sf::Font*>& supported_fonts,
							 const std::map<const std::string, int>& supported_keys)
	: State{ window, states, supported_fonts, supported_keys }, GUI::Menu{ static_cast<sf::Vector2f>(m_window.getSize()) },
	m_title{ "controL of GrounD", *supported_fonts["MAJOR"], 78U }
{
	initTextures();
	initBackground();
	initButtons();
}

MainMenuState::~MainMenuState()
{
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void MainMenuState::initTextures()
{
	m_textures["BACKGROUND"] = new sf::Texture();

	if (!m_textures["BACKGROUND"]->loadFromFile("resources/textures/MainMenu/Background.jpg"))
		throw "ERROR::MainMenuState::init_background - failed to load texture BACKGROUND";
}

void MainMenuState::initBackground()
{
	m_background.setTexture(m_textures["BACKGROUND"]);

	//Title
	m_title.setLetterSpacing(1.5f);
	m_title.setStyle(sf::Text::Bold);

	const float default_position_x = (m_window.getSize().x / 2.f) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = (m_window.getSize().y / 2.f) - (m_title.getGlobalBounds().height / 2.f); // Center

	const float default_offset_y = -300.f;

	m_title.setPosition(default_position_x - 20, default_position_y + default_offset_y);
}

void MainMenuState::initButtons()
{
	unsigned int font_size = 26U;

	const float button_width = 230.f;
	const float button_height = 85.f;

	const float default_position_x = (m_window.getSize().x / 2.f) - (button_width / 2.f); // 150.f;
	const float default_position_y = (m_window.getSize().y / 2.5f) - (button_height / 2.f); // 350.f;
	const float default_offset_between = 120.f;

	m_buttons["GAME_STATE"]   =	new GUI::Button{ sf::Vector2f(default_position_x, default_position_y),
								sf::Vector2f(button_width, button_height),
								*m_supported_fonts["DOSIS"], "New Game", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

	m_buttons["EDITOR_STATE"] = new GUI::Button{ sf::Vector2f(default_position_x, default_position_y + default_offset_between),
								sf::Vector2f(button_width, button_height),
								*m_supported_fonts["DOSIS"], "Editor", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

	m_buttons["SETTINGS"]     =	new GUI::Button{ sf::Vector2f(default_position_x, default_position_y + default_offset_between * 2),
								sf::Vector2f(button_width, button_height),
								*m_supported_fonts["DOSIS"], "Settings", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

	m_buttons["EXIT_STATE"]   =	new GUI::Button{ sf::Vector2f(default_position_x, default_position_y + default_offset_between * 3.5f),
								sf::Vector2f(button_width, button_height),
								*m_supported_fonts["DOSIS"], "Exit", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

}

void MainMenuState::initKeybinds()
{
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void MainMenuState::updateInput(const float& dt)
{
}

void MainMenuState::updateButtons(const sf::Vector2f& mouse_pos)
{
	for (auto& i : m_buttons)
		i.second->update(m_mouse_pos_view);

	if (m_buttons["GAME_STATE"]->isPressed())
		m_states.push(new GameState{ m_window, m_states, m_supported_fonts, m_supported_keys });

	if (m_buttons["EDITOR_STATE"]->isPressed())
		m_states.push(new EditorState{ m_window, m_states, m_supported_fonts, m_supported_keys });

	if (m_buttons["SETTINGS"]->isPressed())
	{
		//m_states.push(new EditorState{ m_window, m_states, m_supported_fonts, m_supported_keys });
	}
	
	if (m_buttons["EXIT_STATE"]->isPressed())
		quitState();
}

void MainMenuState::update(const float& dt)
{
	updateMousePos();
	//updateKeyboardInput(dt);
	updateButtons(m_mouse_pos_view);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void MainMenuState::render(sf::RenderTarget& target)
{
	target.draw(m_background);
	target.draw(m_title);

	renderButtons(target);
}

////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string MainMenuState::getStringInfo()
{
	std::stringstream result;

	result << getStringMousePos();

	//Getting info from buttons
	result << Menu::getStringInfo();

	return result.str();
}