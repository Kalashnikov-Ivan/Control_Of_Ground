#include "stdHeader.hpp"

#include "Entity.hpp"

#include "State.hpp"
#include "GameState.hpp"

#define DEBUG

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
GameState::GameState(sf::RenderWindow* window, std::map<const std::string, int>* supported_keys)
	: State(window, supported_keys)
{
	init_keybinds();
}

GameState::~GameState()
{
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void GameState::init_keybinds()
{
	m_keybinds["MOVE_LEFT"] = m_supported_keys->at("A");
	m_keybinds["MOVE_RIGHT"] = m_supported_keys->at("D");
	m_keybinds["MOVE_TOP"] = m_supported_keys->at("W");
	m_keybinds["MOVE_DOWN"] = m_supported_keys->at("S");
}

////////////////////////////////////////////////////////////
// Virtual override
////////////////////////////////////////////////////////////
void GameState::update_input(const float& dt)
{
	check_for_quit();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_LEFT"])))
		m_player.move(dt, -1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_RIGHT"])))
		m_player.move(dt, 1.f, 0.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_TOP"])))
		m_player.move(dt, 0.f, -1.f);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["MOVE_DOWN"])))
		m_player.move(dt, 0.f, 1.f);
}

void GameState::update(const float& dt)
{
	update_input(dt);

	m_player.update(dt);
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = m_window;
		
	m_player.render(target);
}

void GameState::end_state()
{
	std::cout << "State: Ending GameState..." << std::endl;
}