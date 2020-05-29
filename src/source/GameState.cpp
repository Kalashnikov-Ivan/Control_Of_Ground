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
	initTextures();
	initKeybinds();
	initPlayers();
}

GameState::~GameState()
{
	//State delete all textures
	delete m_player;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void GameState::initTextures()
{
	m_textures["PLAYER_SHEET"] = new sf::Texture();

	if (!m_textures["PLAYER_SHEET"]->loadFromFile("resources/textures/Player/adventurer_Sheet.png"))
		throw "ERROR::GameState::init_textures::PLAYER_SHEET - failed to load texture resources/textures/Player/adventurer_Sheet.png";
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

void GameState::initPlayers()
{
	const float max_speed = 500.f;
	m_player = new Player(sf::Vector2f(0.f, 0.f), *m_textures["PLAYER_SHEET"], max_speed, 10.f, 4.f);
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void GameState::updateKeyboardInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"])))
		endState();

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
	updateMousePos();
	updateKeyboardInput(dt);

	m_player->update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (target == nullptr)
		target = &m_window;
		
	m_player->render(target);
	target->draw(getMousePosText(*m_supported_fonts["DOSIS"]));
}

////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string GameState::getStringInfo()
{
	std::stringstream result;

	result << getStringPlayerSpeed();

	return result.str();
}
std::string GameState::getStringPlayerSpeed() const
{
	std::stringstream speed_info;
	speed_info << "p_speed: x = " << m_player->getSpeed().x << " y =" << m_player->getSpeed().y << '\n';

	return speed_info.str();
}