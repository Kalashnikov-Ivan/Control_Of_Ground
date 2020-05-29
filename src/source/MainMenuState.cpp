#include "stdHeader.hpp"

#include "MainMenuState.hpp"

#define DEBUG

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(sf::RenderWindow& window,
							 std::stack<State*>& states,
							 std::map<const std::string, sf::Font*>& supported_fonts,
							 const std::map<const std::string, int>& supported_keys)
	: State{ window, states, supported_fonts, supported_keys },
	m_title{ "controL of GrounD", *supported_fonts["MAJOR"], 78U }
{
	initTextures();
	initBackground();
	initButtons();
}

MainMenuState::~MainMenuState()
{
	deleteButtons();
}

//Support_cleaner
void MainMenuState::deleteButtons()
{
	for (auto& i : m_buttons)
		delete i.second;
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
	m_background.setSize(static_cast<sf::Vector2f>(m_window.getSize()));

	m_background.setTexture(m_textures["BACKGROUND"]);

	//Title
	m_title.setLetterSpacing(1.5f);
	m_title.setStyle(sf::Text::Bold);

	const float default_position_x = (m_window.getSize().x / 2.f) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = (m_window.getSize().y / 2.f) - (m_title.getGlobalBounds().height / 2.f); // Center

	const float default_offset = 250.f;

	m_title.setPosition(default_position_x - 20, default_position_y - default_offset);
}

void MainMenuState::initButtons()
{
	unsigned int font_size = 26U;

	const float button_width = 230.f;
	const float button_height = 85.f;

	const float default_position_x = (m_window.getSize().x / 2.f) - (button_width / 2.f); // 150.f;
	const float default_position_y = (m_window.getSize().y / 2.f) - (button_height / 2.f); // 350.f;
	const float default_offset_between = 120.f;

	m_buttons["GAME_STATE"] = new Button{ sf::Vector2f(default_position_x, default_position_y), 
								sf::Vector2f(button_width, button_height),
								*m_supported_fonts["DOSIS"], "New Game", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

	m_buttons["SETTINGS"] = new Button{ sf::Vector2f(default_position_x, default_position_y + default_offset_between),
								sf::Vector2f(button_width, button_height),
								*m_supported_fonts["DOSIS"], "Settings", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

	m_buttons["EXIT_STATE"] = new Button{ sf::Vector2f(default_position_x, default_position_y + default_offset_between * 2),
								sf::Vector2f(button_width, button_height),
								*m_supported_fonts["DOSIS"], "Exit", font_size,
								sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20,20,20,200) };

}

void MainMenuState::initKeybinds()
{
}


////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string MainMenuState::getStringInfo()
{
	return "";
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void MainMenuState::updateKeyboardInput(const float& dt)
{
}

void MainMenuState::updateButtons(const float& dt)
{
	for (auto& i : m_buttons)
		i.second->update(m_mouse_pos_view);

	if (m_buttons["GAME_STATE"]->isPressed())
		m_states.push(new GameState{ m_window, m_states, m_supported_fonts, m_supported_keys });
	
	if (m_buttons["EXIT_STATE"]->isPressed())
		endState();
}

void MainMenuState::update(const float& dt)
{
	updateMousePos();
	updateKeyboardInput(dt);
	updateButtons(dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void MainMenuState::renderButtons(sf::RenderTarget* target)
{
	for (auto& i : m_buttons)
		i.second->render(target);
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (target == nullptr)
		target = &m_window;

	target->draw(m_background);
	target->draw(m_title);

	renderButtons(target);
	target->draw(getMousePosText(*m_supported_fonts["DOSIS"]));
}