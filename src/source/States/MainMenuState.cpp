#include "stdHeader.hpp"

#include "GameState.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"

#include "MainMenuState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(GeneralValues& ref_GV, std::stack<States::State*>& states)
	: State{ ref_GV },
	m_states{ states },
	m_main_menu{ *ref_GV.window, *ref_GV.supported_fonts["DOSIS"] },
	m_title{ "controL of GrounD",  *ref_GV.supported_fonts["MAJOR"], 78U }
{
	initTextures();
	initBackground();
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
	//Background
	m_background.setSize(static_cast<sf::Vector2f>(m_ref_GV.window->getSize()));
	m_background.setTexture(m_textures["BACKGROUND"]);

	//Title
	m_title.setLetterSpacing(1.5f);
	m_title.setStyle(sf::Text::Bold);

	const float default_position_x = (m_ref_GV.window->getSize().x / 2.f) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = (m_ref_GV.window->getSize().y / 2.f) - (m_title.getGlobalBounds().height / 2.f); // Center
	const float default_offset_y = -300.f;

	m_title.setPosition(default_position_x - 20, default_position_y + default_offset_y);
}

void MainMenuState::initKeybinds()
{
}

void MainMenuState::reset()
{
	initBackground();
	m_main_menu.reset();
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void MainMenuState::updateEvent(const sf::Event& event)
{

}

void MainMenuState::updateInput(const float& dt)
{
	if (m_main_menu.isButtonPressed("GAME_STATE"))
		m_states.push(new GameState{ m_ref_GV, m_states });

	if (m_main_menu.isButtonPressed("EDITOR_STATE"))
		m_states.push(new EditorState{ m_ref_GV });

	if (m_main_menu.isButtonPressed("SETTINGS_STATE"))
		m_states.push(new SettingsState{ m_ref_GV, m_states });

	if (m_main_menu.isButtonPressed("EXIT"))
		quitState();
}

void MainMenuState::update(const float& dt)
{
	updateMousePos();
	m_main_menu.update(m_mouse_pos_view, dt);

	//updateKeyboardInput(dt);
	updateInput(dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void MainMenuState::render(sf::RenderTarget& target)
{
	target.draw(m_background);
	target.draw(m_title);

	m_main_menu.render(target);
}

////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string MainMenuState::getStringInfo()
{
	std::stringstream result;

	result << getStringMousePos();

	//Getting info from buttons
	result << m_main_menu.getStringInfo();

	return result.str();
}