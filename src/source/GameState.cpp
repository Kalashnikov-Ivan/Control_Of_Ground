#include "stdHeader.hpp"

#include "GameState.hpp"

#define DEBUG

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
GameState::GameState(sf::RenderWindow& window,
					 std::stack<State*>& states,
					 std::map<const std::string, sf::Font*>& supported_fonts,
					 const std::map<const std::string, int>& supported_keys)
	: State{ window, states, supported_fonts, supported_keys }
{
	init_textures();
	init_keybinds();
	init_players();
}

GameState::~GameState()
{
	//State delete all textures
	delete m_player;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void GameState::init_textures()
{
	m_textures["PLAYER"] = new sf::Texture();

	if (!m_textures["PLAYER"]->loadFromFile("resources/textures/default_0.png"))
		throw "ERROR::GameState::init_textures - failed to load texture resources/textures/default_0.png";
}

void GameState::init_keybinds()
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
			m_keybinds[key] = m_supported_keys.at(key_value);
		}
	}
	else
	{
		std::cerr << "config/GameState_keybinds.ini - cannot open!"
				  << std::endl
				  << "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_supported_keys.at("Escape");

		m_keybinds["MOVE_LEFT"]  = m_supported_keys.at("A");
		m_keybinds["MOVE_RIGHT"] = m_supported_keys.at("D");
		m_keybinds["MOVE_TOP"]   = m_supported_keys.at("W");
		m_keybinds["MOVE_DOWN"]  = m_supported_keys.at("S");
	}

	keys_ifs.close();

#ifdef DEBUG
	for (auto& i : m_keybinds)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "GameState: init_keybinds is success!" << std::endl;
#endif // DEBUG
}

void GameState::init_players()
{
	const float max_speed = 500.f;
	m_player = new Player(sf::Vector2f(0.f, 0.f), *m_textures["PLAYER"], max_speed, 10.f, 4.f);
}

////////////////////////////////////////////////////////////
// Virtual override
////////////////////////////////////////////////////////////
void GameState::update_keyboard_input(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"])))
		end_state();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_LEFT"])))
		m_player->move(sf::Vector2f(-1.f, 0.f), dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_RIGHT"])))
		m_player->move(sf::Vector2f(1.f, 0.f), dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_TOP"])))
		m_player->move(sf::Vector2f(0.f, -1.f), dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_DOWN"])))
		m_player->move(sf::Vector2f(0.f, 1.f), dt);
}

void GameState::update(const float& dt)
{
	update_mouse_pos();
	update_keyboard_input(dt);

	m_player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (target == nullptr)
		target = &m_window;
		
	m_player->render(target);
	target->draw(get_mouse_pos_text(*m_supported_fonts["DOSIS"]));
}