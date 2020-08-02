#include "stdHeader.hpp"

#include "GUI/Converter.h"

#include "SettingsState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
SettingsState::SettingsState(StateData& Sdata)
	: State        { Sdata },
	m_title        { "settings", *Sdata.supported_fonts["MAJOR"], GUI::Converter::calcCharSize(28, Sdata.settings.m_graphics->m_resolution) },
	m_settings_menu{ Sdata.settings.m_graphics->m_resolution, *Sdata.supported_fonts["DOSIS"], Sdata.settings.m_graphics->m_video_modes },
	m_background   { Sdata.background_anim }
{
	initTextures();
	initBackground(Sdata.settings.m_graphics->m_resolution);
}

SettingsState::~SettingsState()
{
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void SettingsState::initTextures()
{
	/*
	const std::string bg_path = "resources/textures/backgrounds/";

	m_textures["ANIMATED_BG_1"] = new sf::Texture();

	if (!m_textures["ANIMATED_BG_1"]->loadFromFile(bg_path + "animated/1/Animated_BG.png"))
		throw "ERROR::MainMenuState::init_background - failed to load texture ANIMATED_BG_1";
	*/
}

void SettingsState::initBackground(const sf::VideoMode& vm)
{
	//Title
	m_title.setLetterSpacing(1.5f);
	m_title.setStyle(sf::Text::Bold);

	const float default_position_x = GUI::Converter::calc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = GUI::Converter::calc(13.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(default_position_x, default_position_y);
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
		resetSettingsAllStates();
	}

	if (m_settings_menu.isButtonPressed("BACK"))
		quitState();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		quitState();
}

void SettingsState::update(const float& dt)
{
	updateMousePos();
	m_background->update(dt);
	m_settings_menu.update(m_mouse_pos_view, dt);

	//updateKeyboardInput(dt);
	updateInput(dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void SettingsState::render(sf::RenderTarget& target)
{
	m_background->render(target);
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

//Functions
void inline SettingsState::resetSettingsAllStates()
{
	m_Sdata.settings.m_graphics->m_resolution = m_settings_menu.getCurrentVM();

	m_Sdata.window.create(m_settings_menu.getCurrentVM(), "Control Of Ground");
	m_Sdata.window.setFramerateLimit(m_Sdata.settings.m_graphics->m_framerate_limit);

	for (auto& i : m_Sdata.states)
		i->reset(m_Sdata.settings.m_graphics->m_resolution);
}

//Reset
void SettingsState::reset(const sf::VideoMode& vm)
{
	m_title.setCharacterSize(GUI::Converter::calcCharSize(28, vm));

	const float default_position_x = GUI::Converter::calc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = GUI::Converter::calc(13.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(default_position_x, default_position_y);

	m_settings_menu.reset(vm);
}