#include "stdafx.h"

#include "GUI/Converter.h"

#include "SettingsState.hpp"

#define DEBUG

using namespace States;

// Constructors
SettingsState::SettingsState(StateContext& ctx)
	: State        { ctx }
	, m_title      { "settings", *ctx.supportedFonts["MAJOR"], GUI::Converter::СalcCharSize(28, ctx.settings.m_graphics->m_resolution) }
	, m_settingsMenu { ctx.settings.m_graphics->m_resolution, *ctx.supportedFonts["DOSIS"], ctx.settings.m_graphics->m_videoModes }
	, m_background   { ctx.backgroundAnim }
{
	InitTextures();
	InitBackground(ctx.settings.m_graphics->m_resolution);
}

SettingsState::~SettingsState()
{
}

// Init
void SettingsState::InitTextures()
{
	/*
	const std::string bg_path = "resources/textures/backgrounds/";
	
	m_textures["ANIMATED_BG_1"] = new sf::Texture();

	if (!m_textures["ANIMATED_BG_1"]->loadFromFile(bg_path + "animated/1/Animated_BG.png"))
		throw "ERROR::MainMenuState::init_background - failed to load texture ANIMATED_BG_1";
	*/
}

void SettingsState::InitBackground(const sf::VideoMode& vm)
{
	//Title
	m_title.setLetterSpacing(1.5f);
	m_title.setStyle(sf::Text::Bold);

	const float defaultPosition_x = GUI::Converter::Сalc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float defaultPosition_y = GUI::Converter::Сalc(13.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(defaultPosition_x, defaultPosition_y);
}

void SettingsState::InitKeybinds()
{
}

// Update
void SettingsState::UpdateEvent(const sf::Event& event)
{
}

void SettingsState::UpdateInput(const float& dt)
{
	if (m_settingsMenu.IsButtonPressed("APPLY"))
	{
		ResetSettingsAllStates();
	}

	if (m_settingsMenu.IsButtonPressed("BACK"))
		QuitState();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		QuitState();
}

void SettingsState::Update(const float& dt)
{
	UpdateMousePos();
	m_background->Update(dt);
	m_settingsMenu.Update(m_mousePosView, dt);

	//updateKeyboardInput(dt);
	UpdateInput(dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void SettingsState::Render(sf::RenderTarget& target)
{
	m_background->Render(target);
	target.draw(m_title);

	m_settingsMenu.Render(target);
}

////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string SettingsState::GetStringInfo()
{
	std::stringstream result;

	result << GetStringMousePos();

	//Getting info from buttons
	result << m_settingsMenu.GetStringInfo();

	return result.str();
}

//Functions
void inline SettingsState::ResetSettingsAllStates()
{
	m_stateContext.settings.m_graphics->m_resolution = m_settingsMenu.GetCurrentVM();

	m_stateContext.window.create(m_settingsMenu.GetCurrentVM(), "Control Of Ground");
	m_stateContext.window.setFramerateLimit(m_stateContext.settings.m_graphics->m_framerateLimit);

	for (auto& i : m_stateContext.states)
		i->Reset(m_stateContext.settings.m_graphics->m_resolution);
}

//Reset
void SettingsState::Reset(const sf::VideoMode& vm)
{
	m_title.setCharacterSize(GUI::Converter::СalcCharSize(28, vm));

	const float defaultPosition_x = GUI::Converter::Сalc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float defaultPosition_y = GUI::Converter::Сalc(13.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(defaultPosition_x, defaultPosition_y);

	m_settingsMenu.Reset(vm);
}