#include "stdafx.h"

#include "GUI/Converter.h"

#include "GameState.hpp"
#include "EditorState.hpp"
#include "SettingsState.hpp"

#include "MainMenuState.hpp"

#define DEBUG

using namespace States;

//Constructors
MainMenuState::MainMenuState(StateContext& ctx)
	: State     { ctx }
	, m_mainMenu{ 
	             ctx.settings.m_graphics->m_resolution, 
				*ctx.supportedFonts["DOSIS"] 
			    }
	, m_title   { 
				 "control of Ground",  *ctx.supportedFonts["MAJOR"], 
				 GUI::Converter::СalcCharSize(28, ctx.settings.m_graphics->m_resolution)   //1600x900 = ~78U
			    }
{
	InitTextures();
	InitBackground(ctx.settings.m_graphics->m_resolution);
}

MainMenuState::~MainMenuState()
{}

//Init
void MainMenuState::InitTextures()
{
	const std::string root = "resources/textures/";

	m_textures["DEFAULT_BG"] = std::make_shared<sf::Texture>();

	if (!m_textures["DEFAULT_BG"]->loadFromFile(root + "backgrounds/default.png"))
		throw std::runtime_error("MainMenuState::initTextures::DEFAULT_BG - loading texture" + root + 
			"backgrounds/default.png" + " failed...");

	m_textures["ANIMATED_BG_1"] = std::make_shared<sf::Texture>();

	if (!m_textures["ANIMATED_BG_1"]->loadFromFile(root + "backgrounds/animated/1/Animated_BG.png"))
		throw std::runtime_error("MainMenuState::initTextures::ANIMATED_BG_1 - loading texture" + root + 
			"backgrounds/animated/1/Animated_BG.png" + " failed...");
}

void MainMenuState::InitBackground(const sf::VideoMode& vm)
{
	//Background
	m_stateContext.backgroundAnim = std::make_shared<GUI::AnimatedBackground>(sf::Vector2f((float)vm.width, (float)vm.height), *m_textures["ANIMATED_BG_1"]);
	m_background = m_stateContext.backgroundAnim;

	//Title
	m_title.setLetterSpacing(1.5f);
	m_title.setStyle(sf::Text::Bold);

	const float defaultPosition_x = GUI::Converter::Сalc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float defaultPosition_y = GUI::Converter::Сalc(13.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(defaultPosition_x, defaultPosition_y);
}

void MainMenuState::InitKeybinds()
{
}

//Update
void MainMenuState::UpdateEvent(const sf::Event& event)
{

}

void MainMenuState::UpdateInput(const float& dt)
{
	if (m_mainMenu.IsButtonPressed("GAME_STATE"))
		m_stateContext.states.push_back(std::make_unique<GameState>(m_stateContext));

	if (m_mainMenu.IsButtonPressed("EDITOR_STATE"))
		m_stateContext.states.push_back(std::make_unique<EditorState>(m_stateContext));

	if (m_mainMenu.IsButtonPressed("SETTINGS_STATE"))
		m_stateContext.states.push_back(std::make_unique<SettingsState>(m_stateContext));

	if (m_mainMenu.IsButtonPressed("EXIT"))
		QuitState();
}

void MainMenuState::Update(const float& dt)
{
	UpdateMousePos();
	m_background->Update(dt);
	m_mainMenu.Update(m_mousePosView, dt);

	//updateKeyboardInput(dt);
	UpdateInput(dt);
}

//Render
void MainMenuState::Render(sf::RenderTarget& target)
{
	m_background->Render(target);
	target.draw(m_title);

	m_mainMenu.Render(target);
}

//Tech info
std::string MainMenuState::GetStringInfo()
{
	std::stringstream result;

	result << GetStringMousePos();

	//Getting info from buttons
	result << m_mainMenu.GetStringInfo();

	return result.str();
}

//Reset
void MainMenuState::Reset(const sf::VideoMode& vm)
{
	//Title
	m_title.setCharacterSize(GUI::Converter::СalcCharSize(28, vm));

	const float defaultPosition_x = GUI::Converter::Сalc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float defaultPosition_y = GUI::Converter::Сalc(13.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(defaultPosition_x, defaultPosition_y);

	m_mainMenu.Reset(vm);
	m_background->Reset(vm);
}