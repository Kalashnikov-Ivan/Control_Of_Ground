#include "stdHeader.hpp"

#include "SettingsState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
SettingsState::SettingsState(sf::RenderWindow& window,
							 std::stack<State*>& states,
							 std::map<const std::string, sf::Font*>& supported_fonts,
							 const std::map<const std::string, int>& supported_keys)
	: State{ window, states, supported_fonts, supported_keys },
	m_title{ "settings", *supported_fonts["MAJOR"], 78U },
	m_video_modes { sf::VideoMode(1920, 1080), sf::VideoMode(1600, 900), sf::VideoMode(1280, 1024), 
					sf::VideoMode(1024, 768), sf::VideoMode(800, 600) },
	m_settings_menu{ window, *supported_fonts["DOSIS"], m_video_modes }
{
	initTextures();
	initBackground();
}

SettingsState::~SettingsState()
{
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void SettingsState::initTextures()
{
	m_textures["BACKGROUND"] = new sf::Texture();

	if (!m_textures["BACKGROUND"]->loadFromFile("resources/textures/MainMenu/Background.jpg"))
		throw "ERROR::MainMenuState::init_background - failed to load texture BACKGROUND";
}

void SettingsState::initBackground()
{
	//Background
	m_background.setSize(static_cast<sf::Vector2f>(m_window.getSize()));
	m_background.setTexture(m_textures["BACKGROUND"]);

	//Title
	m_title.setLetterSpacing(1.5f);
	m_title.setStyle(sf::Text::Bold);

	const float default_position_x = (m_window.getSize().x / 2.f) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = (m_window.getSize().y / 2.f) - (m_title.getGlobalBounds().height / 2.f); // Center
	const float default_offset_y = -300.f;

	m_title.setPosition(default_position_x - 20, default_position_y + default_offset_y);
}

void SettingsState::initKeybinds()
{
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void SettingsState::updateEvent(const sf::Event& event)
{
}

void SettingsState::updateInput(const float& dt)
{
	if (m_settings_menu.isButtonPressed("APPLY"))
	{
		m_window.create(m_settings_menu.getCurrentVM(), "Control Of Ground");
	}

	if (m_settings_menu.isButtonPressed("BACK"))
		quitState();
}

void SettingsState::update(const float& dt)
{
	updateMousePos();
	m_settings_menu.update(m_mouse_pos_view, dt);

	//updateKeyboardInput(dt);
	updateInput(dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void SettingsState::render(sf::RenderTarget& target)
{
	target.draw(m_background);
	target.draw(m_title);

	m_settings_menu.render(target);
}

////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string SettingsState::getStringInfo()
{
	std::stringstream result;

	result << getStringMousePos();

	//Getting info from buttons
	result << m_settings_menu.getStringInfo();

	return result.str();
}