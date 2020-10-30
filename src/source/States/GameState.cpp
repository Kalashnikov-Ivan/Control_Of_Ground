#include "stdafx.h"

#include "GameState.hpp"
#include "SettingsState.hpp"

#define DEBUG

using namespace States;

// Constructors
GameState::GameState(StateContext& ctx)
	: State      { ctx }
	, m_pauseMenu{ ctx.settings.m_graphics->m_resolution, *ctx.supportedFonts["DOSIS"], ctx.supportedFonts }
	, m_tileMap  { sf::Vector2f(100.f, 100.f), sf::Vector2u(100, 10), nullptr }
	, m_player   { nullptr }
{
	InitTextures();
	InitKeybinds();
	InitPlayers();
}

GameState::~GameState()
{
	//State delete all textures
}

// Init
void GameState::InitTextures()
{
	const std::string root = "resources/textures/";

	m_textures["PLAYER_SHEET"] = std::make_shared<sf::Texture>();

	if (!m_textures["PLAYER_SHEET"]->loadFromFile(root + "Player/Player_sheet.png"))
		throw std::runtime_error("GameState::initTextures::PLAYER_SHEET - loading texture" + root + "Player/Player_sheet.png" + " failed...");
}

void GameState::InitKeybinds()
{
#ifdef DEBUG
	std::cout << "\nGameState: Start of init_keybinds..." << std::endl;
#endif // DEBUG

	std::ifstream keysIfs("config/GameState_keybinds.ini");
	if (keysIfs.is_open())
	{
		std::string key{ "" };
		std::string val{ "" };

		while (keysIfs >> key >> val)
		{
			m_keybinds[key] = m_stateContext.supportedKeys.at(val);
		}
	}
	else
	{
		std::cerr << "config/GameState_keybinds.ini - cannot open!"
				  << std::endl
				  << "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_stateContext.supportedKeys.at("Escape");

		m_keybinds["MOVE_LEFT"]  = m_stateContext.supportedKeys.at("A");
		m_keybinds["MOVE_RIGHT"] = m_stateContext.supportedKeys.at("D");
		m_keybinds["MOVE_TOP"]   = m_stateContext.supportedKeys.at("W");
		m_keybinds["MOVE_DOWN"]  = m_stateContext.supportedKeys.at("S");
	}

#ifdef DEBUG
	for (auto& i : m_keybinds)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "GameState: init_keybinds is success!" << std::endl;
#endif // DEBUG
}

void GameState::InitPlayers()
{
	const float max_speed = 500.f;
	m_player = std::make_unique<Entities::Player>(sf::Vector2f(10.f, 100.f), *m_textures["PLAYER_SHEET"], max_speed, 2.f, 1.f, sf::Vector2f(4.f, 4.f));
}

// Update
void GameState::UpdateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::LostFocus)
	{
		if (!m_paused)
			Pause();
	}

	if (event.type == sf::Event::KeyPressed)
	{ 

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["CLOSE"])))
		{
			if (!m_paused)
				Pause();
			else
				Unpause();
		}

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["SWITCH_TILE_BORDER_VISIBLE"])))
		{
			if (!m_tileMap.GetTilesBorderVisible())
				m_tileMap.SetTilesBorderVisible(true);
			else
				m_tileMap.SetTilesBorderVisible(false);
		}
	}

}

void GameState::UpdateInput(const float& dt)
{
}

void GameState::updatePauseInput(const float& dt)
{
	if (m_pauseMenu.IsButtonPressed("SETTINGS_STATE"))
		m_stateContext.states.push_back(std::make_unique<SettingsState>(m_stateContext));

	if (m_pauseMenu.IsButtonPressed("EXIT"))
		QuitState();
}

void GameState::updatePlayerInput(const float& dt)
{
	bool keyPressed{ false };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_LEFT"])))
	{
		keyPressed = true;
		m_player->Move(sf::Vector2f(-1.f, 0.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_RIGHT"])))
	{
		keyPressed = true;
		m_player->Move(sf::Vector2f(1.f, 0.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_TOP"])))
	{
		keyPressed = true;
		m_player->Move(sf::Vector2f(0.f, -1.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_DOWN"])))
	{
		keyPressed = true;
		m_player->Move(sf::Vector2f(0.f, 1.f), dt);
	}

	if (!keyPressed)
		m_player->Move(sf::Vector2f(0.f, 0.f), dt);
}

void GameState::Update(const float& dt)
{
	UpdateMousePos();

	if (!m_paused)
	{
		updatePlayerInput(dt);

		m_player->Update(dt);
	}
	else
	{
		updatePauseInput(dt);

		m_pauseMenu.Update(m_mousePosView, dt);
	}
}

void GameState::Render(sf::RenderTarget& target)
{		
	m_tileMap.Render(target);

	m_player->Render(target);

	if (m_paused)
	{
		m_pauseMenu.Render(target);
	}
}

// Tech info
std::string GameState::GetStringInfo()
{
	std::stringstream result;

	result << GetStringMousePos();
	result << m_player->GetStringInfo();
	result << m_pauseMenu.GetStringInfo();

	return result.str();
}

//Reset
void GameState::Reset(const sf::VideoMode& vm)
{
	m_pauseMenu.Reset(vm);
}