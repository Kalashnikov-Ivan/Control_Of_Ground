#include "stdHeader.hpp"

#include "GUI/Converter.h"

#include "GameState.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"

#include "MainMenuState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenuState::MainMenuState(StateData& Sdata)
	: State{ Sdata },
	m_main_menu{ Sdata.settings.m_graphics->m_resolution, 
				*Sdata.supported_fonts["DOSIS"] },
	m_title{ "control of Ground",  *Sdata.supported_fonts["MAJOR"], 
			 GUI::Converter::calcCharSize(28, Sdata.settings.m_graphics->m_resolution)   //1600x900 = ~78U
		   }
{
	initTextures();
	initBackground(Sdata.settings.m_graphics->m_resolution);
}

MainMenuState::~MainMenuState()
{
	delete m_Sdata.background_anim;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void MainMenuState::initTextures()
{
	const std::string root = "resources/textures/";

	m_textures["DEFAULT_BG"] = new sf::Texture();

	if (!m_textures["DEFAULT_BG"]->loadFromFile(root + "backgrounds/default.png"))
		throw std::runtime_error("MainMenuState::initTextures::DEFAULT_BG - loading texture" + root + "backgrounds/default.png" + " failed...");

	m_textures["ANIMATED_BG_1"] = new sf::Texture();

	if (!m_textures["ANIMATED_BG_1"]->loadFromFile(root + "backgrounds/animated/1/Animated_BG.png"))
		throw std::runtime_error("MainMenuState::initTextures::ANIMATED_BG_1 - loading texture" + root + "backgrounds/animated/1/Animated_BG.png" + " failed...");
}

void MainMenuState::initBackground(const sf::VideoMode& vm)
{
	//Background
	m_Sdata.background_anim = new GUI::AnimatedBackground(sf::Vector2f((float)vm.width, (float)vm.height), *m_textures["ANIMATED_BG_1"]);
	m_background = m_Sdata.background_anim;

	//Title
	m_title.setLetterSpacing(1.5f);
	m_title.setStyle(sf::Text::Bold);

	const float default_position_x = GUI::Converter::calc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = GUI::Converter::calc(13.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(default_position_x, default_position_y);
}

void MainMenuState::initKeybinds()
{
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
		m_Sdata.states.push(new GameState{ m_Sdata });

	if (m_main_menu.isButtonPressed("EDITOR_STATE"))
		m_Sdata.states.push(new EditorState{ m_Sdata });

	if (m_main_menu.isButtonPressed("SETTINGS_STATE"))
		m_Sdata.states.push(new SettingsState{ m_Sdata });

	if (m_main_menu.isButtonPressed("EXIT"))
		quitState();
}

void MainMenuState::update(const float& dt)
{
	updateMousePos();
	m_background->update(dt);
	m_main_menu.update(m_mouse_pos_view, dt);

	//updateKeyboardInput(dt);
	updateInput(dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void MainMenuState::render(sf::RenderTarget& target)
{
	m_background->render(target);
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

//Reset
void MainMenuState::reset(const sf::VideoMode& vm)
{
	//Title
	m_title.setCharacterSize(GUI::Converter::calcCharSize(28, vm));

	const float default_position_x = GUI::Converter::calc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = GUI::Converter::calc(13.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(default_position_x, default_position_y);

	m_main_menu.reset(vm);
	m_background->reset(vm);
}