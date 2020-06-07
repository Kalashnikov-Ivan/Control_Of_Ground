#include "stdHeader.hpp"

#include "EditorState.hpp"

#define DEBUG

using namespace States;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////

EditorState::EditorState(sf::RenderWindow& window,
						 std::stack<State*>& states,
						 std::map<const std::string, sf::Font*>& supported_fonts,
						 const std::map<const std::string, int>& supported_keys)
	: State{ window, states, supported_fonts, supported_keys }
{
	initTextures();
	initKeybinds();
}

EditorState::~EditorState()
{
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void EditorState::initTextures()
{
}

void EditorState::initKeybinds()
{
#ifdef DEBUG
	std::cout << "EditorState: Start of init_keybinds..." << std::endl;
#endif // DEBUG

	std::ifstream keys_ifs("config/EditorState_keybinds.ini");
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
		std::cerr << "config/EditorState.ini - cannot open!"
			<< std::endl
			<< "Using default keys..." << std::endl;

		m_keybinds["CLOSE"] = m_supported_keys.at("Escape");
	}

	keys_ifs.close();

#ifdef DEBUG
	for (auto& i : m_keybinds)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "EditorState: init_keybinds is success!" << std::endl;
#endif // DEBUG
}


////////////////////////////////////////////////////////////
// Tech info
////////////////////////////////////////////////////////////
std::string EditorState::getStringInfo()
{
	std::stringstream result;

	result << getStringMousePos();

	return result.str();
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void EditorState::updateEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window.close();

		if (event.type == sf::Event::KeyPressed)
		{
			/*
			if (event.key.code == (sf::Keyboard::Key(m_supported_keys["F3"])))
			{
				if (m_enable_info)
					m_enable_info = false;
				else
					m_enable_info = true;
			}
			*/
		}
	}
}

void EditorState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_keybinds["CLOSE"])))
		quitState();
}

void EditorState::update(const float& dt)
{
	updateMousePos();
	updateInput(dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void EditorState::render(sf::RenderTarget& target)
{
}