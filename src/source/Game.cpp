#include "stdafx.h"
//#include "GeneralValues.h"

#include "States/MainMenuState.hpp"

#include "Game.hpp"

#define DEBUG

using namespace Core;

// Constructors
Game::Game()
	: m_dt{ 0.f }
	, m_enableInfo { true }
{
	InitSettings();
	InitWindow(); //Dynamic for window
	InitSupportedKeys();
	InitSupportedFonts(); //Dynamic for fonts
	InitFirstState(); //Dynamic for first state
}

Game::~Game()
{}

// Init
void inline Game::InitSettings()
{
	m_settings.InitGraphics(
		"config/graphics.ini",
		{ sf::VideoMode(1920, 1080), sf::VideoMode(1600, 900), sf::VideoMode(1280, 1024), sf::VideoMode(1024, 768), sf::VideoMode(800, 600) }
	);
}

void Game::InitWindow()
{
	const std::string title = "Control of Ground";

	unsigned int style = sf::Style::Titlebar | sf::Style::Close;
	if (m_settings.m_graphics->m_fullscreen)
		style = sf::Style::Fullscreen;

	m_window = std::make_unique<sf::RenderWindow>(
		m_settings.m_graphics->m_resolution, title,  
		style
		);

	m_window->setFramerateLimit     (m_settings.m_graphics->m_framerateLimit);
	m_window->setVerticalSyncEnabled(m_settings.m_graphics->m_vsync);
	//window->setKeyRepeatEnabled(false);
}

void Game::InitSupportedKeys()
{
#ifdef DEBUG
	std::cout << "Game: Start of init_supported_keys..." << std::endl;
#endif // DEBUG

	std::ifstream keysIfs("config/supported_keys.ini");
	if (keysIfs.is_open())
	{
		std::string key{ "" };
		int val{ 0 };

		while (keysIfs >> key >> val)
		{
			m_supportedKeys[key] = val;
		}
	}
	else
	{
		std::cerr << "config/supported_keys.ini - cannot open!"
		          << std::endl
			      << "Using default keys..." << std::endl;

		m_supportedKeys["Escape"] = sf::Keyboard::Escape;
		m_supportedKeys["F3"]     = sf::Keyboard::F3;

		m_supportedKeys["A"] = sf::Keyboard::A;
		m_supportedKeys["D"] = sf::Keyboard::D;
		m_supportedKeys["W"] = sf::Keyboard::W;
		m_supportedKeys["S"] = sf::Keyboard::S;
	}

	keysIfs.close();

#ifdef DEBUG
	for (auto& i : m_supportedKeys)
		std::cout << i.first << " = " << i.second << std::endl;

	std::cout << "Game: init_supported_keys is success!" << std::endl;
#endif // DEBUG
}

void Game::InitSupportedFonts()
{
	const std::string path = "resources/fonts/";

	m_supportedFonts["DOSIS"] = std::make_unique<sf::Font>();
	if (!m_supportedFonts["DOSIS"]->loadFromFile(path + "Dosis-Regular.ttf"))
		throw std::runtime_error("Game::initSupportedFonts. Can't open: fonts/Dosis-Regular.ttf");

	m_supportedFonts["OSWALD"] = std::make_unique<sf::Font>();
	if (!m_supportedFonts["OSWALD"]->loadFromFile(path + "Oswald-SemiBold.ttf"))
		throw std::runtime_error("Game::initSupportedFonts. Can't open: fonts/Oswald-SemiBold.ttf");

	m_supportedFonts["MAJOR"] = std::make_unique<sf::Font>();
	if (!m_supportedFonts["MAJOR"]->loadFromFile(path + "MajorMonoDisplay-Regular.ttf"))
		throw std::runtime_error("Game::initSupportedFonts. Can't open: fonts/MajorMonoDisplay-Regular.ttf");
}

void Game::InitFirstState()
{
	const size_t reserveForStates = 5;
	sf::Vector2f gridSize{ 64.f, 64.f };

	m_stateContext = std::make_unique<States::StateContext>(*m_window, m_states, m_settings, m_supportedKeys, m_supportedFonts, gridSize);

	m_states.reserve(reserveForStates);
	m_states.push_back(std::make_unique<States::MainMenuState>(*m_stateContext));
}

// Info
void Game::UpdateInfo()
{
	m_techInfo.str(std::string()); //Clearing
	m_mouseInfo.str(std::string());

	m_techInfo << "Delta time: " << m_dt << " sec" << ", FPS: " << static_cast<uint32_t>(1 / m_dt) << '\n';
}

sf::Text Game::GetTextInfo(const sf::Font& font)
{
	sf::Text info_text{ m_techInfo.str(), font, 16U };
	info_text.setPosition(20.f, 20.f);

	return info_text;
}

sf::Text Core::Game::GetMouseTextInfo(const sf::Font& font)
{
	sf::Text info_text{ m_mouseInfo.str(), font, 12U };
	info_text.setPosition(
		m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)).x + 15, 
		m_window->mapPixelToCoords(sf::Mouse::getPosition(*m_window)).y - 15);

	return info_text;
}

// Update and Render
void Game::UpdateDeltaTime()
{
	m_dt = m_dtClock.restart().asSeconds();
}

void Game::UpdateEvents()
{
	sf::Event event;
	while (m_window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			m_window->close();

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == (sf::Keyboard::Key(m_supportedKeys["F3"])))
			{
				if (m_enableInfo)
					m_enableInfo = false;
				else
					m_enableInfo = true;
			}
		}
		m_states.back()->UpdateEvent(event);
	}
}

void Game::Update()
{
	if (m_enableInfo)
		UpdateInfo();

	if (!m_states.empty())
	{
		//Update the top state
		UpdateEvents();
		m_states.back()->Update(m_dt);

		//Getting info
		if (m_enableInfo)
		{
			m_techInfo  << m_states.back()->GetStringInfo();
			m_mouseInfo << m_states.back()->GetStringInfoMouse();
		}

		//Check quit
		if (m_states.back()->GetQuit())
			m_states.pop_back();
	}
	else //Application end
	{
		ApplicationEnd();
		m_window->close();
	}
}

void Game::ApplicationEnd()
{
	std::cout << "Application: Control of Ground is end..." << std::endl;
}

void Game::Render()
{
	m_window->clear(sf::Color::Black);

	if (!m_states.empty())
	{
		m_states.back()->Render(*m_window);
	}

	if (m_enableInfo)
	{
		m_window->draw(GetTextInfo(*m_supportedFonts["DOSIS"]));
		m_window->draw(GetMouseTextInfo(*m_supportedFonts["DOSIS"]));
	}

	m_window->display();
}

// Core
void Game::Run()
{
	while (m_window->isOpen())
	{
		UpdateDeltaTime();

		Update();
		Render();
	}
}