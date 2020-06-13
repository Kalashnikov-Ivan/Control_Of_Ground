#include "stdHeader.hpp"
#include "GeneralValues.h"

#include "States/MainMenuState.hpp"

#include "Game.hpp"

#define DEBUG

using namespace Core;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Game::Game()
	: m_delta_time{ 0.f },
	m_enable_info{ true }
{
	initSettings();
	initWindow(); //Dynamic for window
	initSupportedKeys();
	initSupportedFonts(); //Dynamic for fonts
	initFirstState(); //Dynamic for first state
}

Game::~Game()
{
	deleteStates();
	deleteFonts();

	delete m_GV.window;
}

//Support_cleaner
void Game::deleteStates()
{
	while (!m_states.empty())
	{
		delete m_states.top();
		m_states.pop();
	}
}
void Game::deleteFonts()
{
	for (auto& i : m_GV.supported_fonts)
		delete i.second;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void inline Game::initSettings()
{
	m_GV.settings.initGraphics(
		"config/graphics.ini",
		{ sf::VideoMode(1920, 1080), sf::VideoMode(1600, 900), sf::VideoMode(1280, 1024),
		  sf::VideoMode(1024, 768), sf::VideoMode(800, 600) }
	);
}

void Game::initWindow()
{
	std::string title = "Control of Ground";

	if (m_GV.settings.m_graphics->m_fullscreen)
		m_GV.window = new sf::RenderWindow{ m_GV.settings.m_graphics->m_resolution, title,  
											  sf::Style::Fullscreen, m_GV.settings.m_graphics->m_context };
	else
		m_GV.window = new sf::RenderWindow{ m_GV.settings.m_graphics->m_resolution, title,  
											  sf::Style::Titlebar | sf::Style::Close, m_GV.settings.m_graphics->m_context };

	if (m_GV.window == nullptr)
	{
		std::cerr << "Fault of init_window! Is nullptr..." << std::endl;
		throw std::runtime_error("Fault of init_window! Is nullptr...");
	}

	m_GV.window->setFramerateLimit     (m_GV.settings.m_graphics->m_framerate_limit);
	m_GV.window->setVerticalSyncEnabled(m_GV.settings.m_graphics->m_vsync);
	//window->setKeyRepeatEnabled(false);
}

void Game::initSupportedKeys()
{
#ifdef DEBUG
	std::cout << "Game: Start of init_supported_keys..." << std::endl;
#endif // DEBUG

	std::ifstream keys_ifs("config/supported_keys.ini");
	if (keys_ifs.is_open())
	{
		std::string key{ "" };
		int key_value{ 0 };

		while (keys_ifs >> key >> key_value)
		{
			m_GV.supported_keys[key] = key_value;
		}
	}
	else
	{
		std::cerr << "config/supported_keys.ini - cannot open!"
			<< std::endl
			<< "Using default keys..." << std::endl;

		m_GV.supported_keys["Escape"] = sf::Keyboard::Escape;
		m_GV.supported_keys["F3"] = sf::Keyboard::F3;

		m_GV.supported_keys["A"] = sf::Keyboard::A;
		m_GV.supported_keys["D"] = sf::Keyboard::D;
		m_GV.supported_keys["W"] = sf::Keyboard::W;
		m_GV.supported_keys["S"] = sf::Keyboard::S;
	}

	keys_ifs.close();

#ifdef DEBUG
	for (auto& i : m_GV.supported_keys)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "Game: init_supported_keys is success!" << std::endl;
#endif // DEBUG
}

void Game::initSupportedFonts()
{
	const std::string path = "resources/fonts/";

	m_GV.supported_fonts["DOSIS"] = new sf::Font();
	if (!m_GV.supported_fonts["DOSIS"]->loadFromFile(path + "Dosis-Regular.ttf"))
		throw "ERROR::MainMenuState: init_fonts. Can't open font fonts/Dosis-Regular.ttf";

	m_GV.supported_fonts["OSWALD"] = new sf::Font();
	if (!m_GV.supported_fonts["OSWALD"]->loadFromFile(path + "Oswald-SemiBold.ttf"))
		throw "ERROR::MainMenuState: init_fonts. Can't open font fonts/Oswald-SemiBold.ttf";

	m_GV.supported_fonts["MAJOR"] = new sf::Font();
	if (!m_GV.supported_fonts["MAJOR"]->loadFromFile(path + "MajorMonoDisplay-Regular.ttf"))
		throw "ERROR::MainMenuState: init_fonts. Can't open font fonts/MajorMonoDisplay-Regular.ttf";

}

void Game::initFirstState()
{
	m_states.push(new States::MainMenuState(m_GV, m_states));
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
void Game::updateInfo()
{
	m_tech_info.str(std::string()); //Clearing

	m_tech_info << "Delta time: " << m_delta_time << " sec" << ", FPS: " << static_cast<uint32_t>(1 / m_delta_time) << '\n';
}

sf::Text Game::getTextInfo(const sf::Font& font)
{
	sf::Text info_text{ m_tech_info.str(), font, 16U };
	info_text.setPosition(20.f, 20.f);

	return info_text;
}

////////////////////////////////////////////////////////////
// Update and render
////////////////////////////////////////////////////////////
void Game::updateDeltaTime()
{
	m_delta_time = m_delta_time_clock.restart().asSeconds();
}

void Game::updateEvents()
{
	sf::Event event;
	while (m_GV.window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_GV.window->close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == (sf::Keyboard::Key(m_GV.supported_keys["F3"])))
			{
				if (m_enable_info)
					m_enable_info = false;
				else
					m_enable_info = true;
			}
		}
		m_states.top()->updateEvent(event);
	}
}

void Game::update()
{
	updateInfo();

	if (!m_states.empty())
	{
		//Update the top state
		updateEvents();
		m_states.top()->update(m_delta_time);

		//Getting info
		if (m_enable_info)
			m_tech_info << m_states.top()->getStringInfo();

		//Check quit
		if (m_states.top()->getQuit())
		{
			m_states.top()->quitState();
			delete m_states.top();
			m_states.pop();
		}
	}
	else //Application end
	{
		applicationEnd();
		m_GV.window->close();
	}
}

void Game::applicationEnd()
{
	std::cout << "Application: Control of Ground is end..." << std::endl;
}

void Game::render()
{
	m_GV.window->clear(sf::Color::Black);

	if (!m_states.empty())
	{
		m_states.top()->render(*m_GV.window);
	}

	if (m_enable_info)
		m_GV.window->draw(getTextInfo(*m_GV.supported_fonts["DOSIS"]));

	m_GV.window->display();
}

////////////////////////////////////////////////////////////
// Core
////////////////////////////////////////////////////////////
void Game::run()
{
	while (m_GV.window->isOpen())
	{
		updateDeltaTime();

		update();
		render();
	}
}