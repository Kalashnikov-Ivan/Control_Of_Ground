#include "stdHeader.hpp"

#include "GameState.hpp"
#include "SettingsState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
GameState::GameState(GeneralValues& ref_GV, std::stack<States::State*>& states)
	: State      { ref_GV },
	m_states     { states },
	m_pause_menu { *ref_GV.window, *ref_GV.supported_fonts["DOSIS"], ref_GV.supported_fonts },
	m_tile_map   { sf::Vector2f(100.f, 100.f), sf::Vector2u(100, 10) }
{
	initTextures();
	initKeybinds();
	initPlayers();
}

GameState::~GameState()
{
	//State delete all textures
	delete m_player;
	std::cout << "GAME STATE DEAD";
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void GameState::initTextures()
{
	m_textures["PLAYER_SHEET"] = new sf::Texture();

	if (!m_textures["PLAYER_SHEET"]->loadFromFile("resources/textures/Player/Player_sheet.png"))
		throw "ERROR::GameState::init_textures::PLAYER_SHEET - failed to load texture resources/textures/Player/Player_sheet.png";
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
			m_keybinds[key] = m_ref_GV.supported_keys.at(key_value);
		}
	}
	else
	{
		std::cerr << "config/GameState_keybinds.ini - cannot open!"
				  << std::endl
				  << "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_ref_GV.supported_keys.at("Escape");

		m_keybinds["MOVE_LEFT"]  = m_ref_GV.supported_keys.at("A");
		m_keybinds["MOVE_RIGHT"] = m_ref_GV.supported_keys.at("D");
		m_keybinds["MOVE_TOP"]   = m_ref_GV.supported_keys.at("W");
		m_keybinds["MOVE_DOWN"]  = m_ref_GV.supported_keys.at("S");
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
	m_player = new Entities::Player(sf::Vector2f(10.f, 100.f), *m_textures["PLAYER_SHEET"], max_speed, 2.f, 1.f, sf::Vector2f(4.f, 4.f));
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
	}
}

void GameState::updateInput(const float& dt)
{
}

void GameState::updatePauseInput(const float& dt)
{
	if (m_pause_menu.isButtonPressed("SETTINGS_STATE"))
		m_states.push(new SettingsState{ m_ref_GV, m_states });

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