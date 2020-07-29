#include "stdHeader.hpp"

#include "GameState.hpp"
#include "SettingsState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
GameState::GameState(StateData& Sdata)
	: State      { Sdata },
	m_pause_menu { Sdata.settings.m_graphics->m_resolution, *Sdata.supported_fonts["DOSIS"], Sdata.supported_fonts },
	m_tile_map   { sf::Vector2f(100.f, 100.f), sf::Vector2u(100, 10), nullptr },
	m_player     { nullptr }
{
	initTextures();
	initKeybinds();
	initPlayers();
}

GameState::~GameState()
{
	//State delete all textures
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void GameState::initTextures()
{
	const std::string root = "resources/textures/";

	m_textures["PLAYER_SHEET"] = new sf::Texture();

	if (!m_textures["PLAYER_SHEET"]->loadFromFile(root + "Player/Player_sheet.png"))
		throw std::runtime_error("GameState::initTextures::PLAYER_SHEET - loading texture" + root + "Player/Player_sheet.png" + " failed...");
}

void GameState::initKeybinds()
{
#ifdef DEBUG
	std::cout << "\nGameState: Start of init_keybinds..." << std::endl;
#endif // DEBUG

	std::ifstream keys_ifs("config/GameState_keybinds.ini");
	if (keys_ifs.is_open())
	{
		std::string key{ "" };
		std::string key_value{ "" };

		while (keys_ifs >> key >> key_value)
		{
			m_keybinds[key] = m_Sdata.supported_keys.at(key_value);
		}
	}
	else
	{
		std::cerr << "config/GameState_keybinds.ini - cannot open!"
				  << std::endl
				  << "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_Sdata.supported_keys.at("Escape");

		m_keybinds["MOVE_LEFT"]  = m_Sdata.supported_keys.at("A");
		m_keybinds["MOVE_RIGHT"] = m_Sdata.supported_keys.at("D");
		m_keybinds["MOVE_TOP"]   = m_Sdata.supported_keys.at("W");
		m_keybinds["MOVE_DOWN"]  = m_Sdata.supported_keys.at("S");
	}

	keys_ifs.close();

#ifdef DEBUG
	for (auto& i : m_keybinds)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "GameState: init_keybinds is success!" << std::endl;
#endif // DEBUG
}

void GameState::initPlayers()
{
	const float max_speed = 500.f;
	m_player = std::make_unique<Entities::Player>(sf::Vector2f(10.f, 100.f), *m_textures["PLAYER_SHEET"], max_speed, 2.f, 1.f, sf::Vector2f(4.f, 4.f));
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void GameState::updateEvent(const sf::Event& event)
{
	if (event.type == sf::Event::LostFocus)
	{
		if (!m_paused)
			pause();
	}

	if (event.type == sf::Event::KeyPressed)
	{ 

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["CLOSE"])))
		{
			if (!m_paused)
				pause();
			else
				unpause();
		}

		if (event.key.code == (sf::Keyboard::Key(m_keybinds["SWITCH_TILE_BORDER_VISIBLE"])))
		{
			if (!m_tile_map.getTilesBorderVisible())
				m_tile_map.setTilesBorderVisible(true);
			else
				m_tile_map.setTilesBorderVisible(false);
		}
	}

}

void GameState::updateInput(const float& dt)
{
}

void GameState::updatePauseInput(const float& dt)
{
	if (m_pause_menu.isButtonPressed("SETTINGS_STATE"))
		m_Sdata.states.push(new SettingsState{ m_Sdata });

	if (m_pause_menu.isButtonPressed("EXIT"))
		quitState();
}

void GameState::updatePlayerInput(const float& dt)
{
	bool key_pressed{ false };

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_LEFT"])))
	{
		key_pressed = true;
		m_player->move(sf::Vector2f(-1.f, 0.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_RIGHT"])))
	{
		key_pressed = true;
		m_player->move(sf::Vector2f(1.f, 0.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_TOP"])))
	{
		key_pressed = true;
		m_player->move(sf::Vector2f(0.f, -1.f), dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_DOWN"])))
	{
		key_pressed = true;
		m_player->move(sf::Vector2f(0.f, 1.f), dt);
	}

	if (!key_pressed)
		m_player->move(sf::Vector2f(0.f, 0.f), dt);
}

void GameState::update(const float& dt)
{
	updateMousePos();

	if (!m_paused)
	{
		updatePlayerInput(dt);

		m_player->update(dt);
	}
	else
	{
		updatePauseInput(dt);

		m_pause_menu.update(m_mouse_pos_view, dt);
	}
}

void GameState::render(sf::RenderTarget& target)
{		
	m_tile_map.render(target);

	m_player->render(target);

	if (m_paused)
	{
		m_pause_menu.render(target);
	}
}

////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string GameState::getStringInfo()
{
	std::stringstream result;

	result << getStringMousePos();
	result << m_player->getStringInfo();
	result << m_pause_menu.getStringInfo();

	return result.str();
}

//Reset
void GameState::reset(const sf::VideoMode& vm)
{
	m_pause_menu.reset(vm);
}