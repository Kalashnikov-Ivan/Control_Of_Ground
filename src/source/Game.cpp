#include "stdHeader.hpp"
//#include "GeneralValues.h"

#include "States/MainMenuState.hpp"

#include "Game.hpp"

#define DEBUG

using namespace Core;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Game::Game()
	: m_delta_time{ 0.f },
	m_enable_info { true }
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
	for (auto& i : m_supported_fonts)
		delete i.second;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void inline Game::initSettings()
{
	m_settings.initGraphics(
		"config/graphics.ini",
		{ sf::VideoMode(1920, 1080), sf::VideoMode(1600, 900), sf::VideoMode(1280, 1024),
		  sf::VideoMode(1024, 768), sf::VideoMode(800, 600) }
	);
}

void Game::initWindow()
{
	const std::string title = "Control of Ground";

	unsigned char style = 0;
	if (m_settings.m_graphics->m_fullscreen)
		style = sf::Style::Fullscreen;
	else
		style = sf::Style::Titlebar | sf::Style::Close;

	m_window = std::make_unique<sf::RenderWindow>(
		m_settings.m_graphics->m_resolution, title,  
		style
		);

	if (m_window == nullptr)
		throw std::runtime_error("Fault of init_window - is nullptr...");

	m_window->setFramerateLimit     (m_settings.m_graphics->m_framerate_limit);
	m_window->setVerticalSyncEnabled(m_settings.m_graphics->m_vsync);
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
			m_supported_keys[key] = key_value;
		}
	}
	else
	{
		std::cerr << "config/supported_keys.ini - cannot open!"
			<< std::endl
			<< "Using default keys..." << std::endl;

		m_supported_keys["Escape"] = sf::Keyboard::Escape;
		m_supported_keys["F3"] = sf::Keyboard::F3;

		m_supported_keys["A"] = sf::Keyboard::A;
		m_supported_keys["D"] = sf::Keyboard::D;
		m_supported_keys["W"] = sf::Keyboard::W;
		m_supported_keys["S"] = sf::Keyboard::S;
	}

	keys_ifs.close();

#ifdef DEBUG
	for (auto& i : m_supported_keys)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "Game: init_supported_keys is success!" << std::endl;
#endif // DEBUG
}

void Game::initSupportedFonts()
{
	const std::string path = "resources/fonts/";

	m_supported_fonts["DOSIS"] = new sf::Font();
	if (!m_supported_fonts["DOSIS"]->loadFromFile(path + "Dosis-Regular.ttf"))
		throw std::runtime_error("Game::initSupportedFonts. Can't open: fonts/Dosis-Regular.ttf");

	m_supported_fonts["OSWALD"] = new sf::Font();
	if (!m_supported_fonts["OSWALD"]->loadFromFile(path + "Oswald-SemiBold.ttf"))
		throw std::runtime_error("Game::initSupportedFonts. Can't open: fonts/Oswald-SemiBold.ttf");

	m_supported_fonts["MAJOR"] = new sf::Font();
	if (!m_supported_fonts["MAJOR"]->loadFromFile(path + "MajorMonoDisplay-Regular.ttf"))
		throw std::runtime_error("Game::initSupportedFonts. Can't open: fonts/MajorMonoDisplay-Regular.ttf");
}

void Game::initFirstState()
{
	sf::Vector2f grid_size{ 64.f, 64.f };

	m_Sdata = make_unique<States::StateData>(*m_window, m_states, m_settings, m_supported_keys, m_supported_fonts, grid_size);

	m_states.push(new States::MainMenuState(*m_Sdata));
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
void Game::updateInfo()
{
	m_tech_info.str(std::string()); //Clearing
	m_mouse_info.str(std::string());

	m_tech_info << "Delta time: " << m_delta_time << " sec" << ", FPS: " << static_cast<uint32_t>(1 / m_delta_time) << '\n';
}

sf::Text Game::getTextInfo(const sf::Font& font)
{
	sf::Text info_text{ m_tech_info.str(), font, 16U };
	info_text.setPosition(20.f, 20.f);

	return info_text;
}

sf::Text Core::Game::getMouseTextInfo(const sf::Font& font)
{
	sf::Text info_text{ m_mouse_info.str(), font, 12U };
	info_text.setPosition(
		m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)).x + 15, 
		m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)).y - 15);

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
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == (sf::Keyboard::Key(m_supported_keys["F3"])))
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
	if (m_enable_info)
		updateInfo();

	if (!m_states.empty())
	{
		//Update the top state
		updateEvents();
		m_states.top()->update(m_delta_time);

		//Getting info
		if (m_enable_info)
		{
			m_tech_info  << m_states.top()->getStringInfo();
			m_mouse_info << m_states.top()->getStringInfoMouse();
		}

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
		m_window->close();
	}
}

void Game::applicationEnd()
{
	std::cout << "Application: Control of Ground is end..." << std::endl;
}

void Game::render()
{
	m_window->clear(sf::Color::Black);

	if (!m_states.empty())
	{
		m_states.top()->render(*m_window);
	}

	if (m_enable_info)
	{
		m_window->draw(getTextInfo(*m_supported_fonts["DOSIS"]));
		m_window->draw(getMouseTextInfo(*m_supported_fonts["DOSIS"]));
	}

	m_window->display();
}

////////////////////////////////////////////////////////////
// Core
////////////////////////////////////////////////////////////
void Game::run()
{
	while (m_window->isOpen())
	{
		updateDeltaTime();

		update();
		render();
	}
}