#include "stdHeader.hpp"

#include "Game.hpp"
#include "MainMenuState.hpp"

#define DEBUG

using namespace Core;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Game::Game()
	: m_window             { nullptr }, 
	  m_video_modes        { sf::VideoMode::getFullscreenModes() }, 
	  m_delta_time         { 0.f },
	  m_fullscreen_enabled { false }, m_enable_info{ true }
{
	initWindow(); //Dynamic for m_window
	initSupportedKeys();
	initSupportedFonts();
	initFirstState(); //Dynamic for first state
}

Game::~Game()
{
	delete_states();
	delete_fonts();

	delete m_window;
}

//Support_cleaner
void Game::delete_states()
{
	while (!m_states.empty())
	{
		delete m_states.top();
		m_states.pop();
	}
}
void Game::delete_fonts()
{
	for (auto& i : m_supported_fonts)
		delete i.second;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
void Game::initWindow()
{
#ifdef DEBUG
	std::cout << "Game: Start of init_window..." << std::endl;
#endif // DEBUG

	//Default
	std::string title = "Control of Ground";
	sf::VideoMode video_mode{ sf::VideoMode::getDesktopMode() };
	unsigned int framerate_limit = 120U;

	m_window_settings.antialiasingLevel = 0U;

	m_fullscreen_enabled = false;
	bool vertical_sync_enabled = false;

	//From file
	std::ifstream window_ini_ifs{ "config/window.ini" }; // window_ini_ifs
	if (window_ini_ifs.is_open())
	{
		std::string option{ "" };
		while (window_ini_ifs >> option)
		{
			if (option == "VIDEO_MODE")
			{
				window_ini_ifs >> video_mode.width;
				window_ini_ifs >> video_mode.height;
			}
			else if (option == "TITLE")
				window_ini_ifs >> title;
			else if (option == "FRAMERATE")
				window_ini_ifs >> framerate_limit;
			else if (option == "ANTIALISING")
				window_ini_ifs >> m_window_settings.antialiasingLevel;
			else if (option == "FULLSCREEN")
				window_ini_ifs >> m_fullscreen_enabled;
			else if (option == "VERTICAL_SYNC")
				window_ini_ifs >> vertical_sync_enabled;
		}
	}
	else
	{
		std::cerr << "config/window.ini - cannot open!"
			<< std::endl
			<< "Using default settings..." << std::endl;
	}
	window_ini_ifs.close(); // !window_ini_ifs

	if (m_fullscreen_enabled)
		m_window = new sf::RenderWindow{ video_mode, title,  sf::Style::Fullscreen, m_window_settings };
	else
		m_window = new sf::RenderWindow{ video_mode, title,  sf::Style::Titlebar | sf::Style::Close, m_window_settings };

	if (m_window == nullptr)
	{
		std::cerr << "Fault of init_window! Is nullptr..." << std::endl;
		throw std::runtime_error("Fault of init_window! Is nullptr...");
	}

	m_window->setFramerateLimit(framerate_limit);
	m_window->setVerticalSyncEnabled(vertical_sync_enabled);
	//m_window->setKeyRepeatEnabled(false);

#ifdef DEBUG
	std::cout << "Init_window successful!\nVideo mode: " << video_mode.width << ", " << video_mode.height << std::endl;
	std::cout << "Frame rate = " << framerate_limit << "\n" << std::endl;
#endif // DEBUG
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
	m_supported_fonts["DOSIS"] = new sf::Font();
	if (!m_supported_fonts["DOSIS"]->loadFromFile("resources/fonts/Dosis-Regular.ttf"))
		throw "ERROR::MainMenuState: init_fonts. Can't open font fonts/Dosis-Regular.ttf";

	m_supported_fonts["OSWALD"] = new sf::Font();
	if (!m_supported_fonts["OSWALD"]->loadFromFile("resources/fonts/Oswald-SemiBold.ttf"))
		throw "ERROR::MainMenuState: init_fonts. Can't open font fonts/Oswald-SemiBold.ttf";

	m_supported_fonts["MAJOR"] = new sf::Font();
	if (!m_supported_fonts["MAJOR"]->loadFromFile("resources/fonts/MajorMonoDisplay-Regular.ttf"))
		throw "ERROR::MainMenuState: init_fonts. Can't open font fonts/MajorMonoDisplay-Regular.ttf";

}

void Game::initFirstState()
{
#ifdef DEBUG
	std::cout << "\nGame: Start of init_states..." << std::endl;
#endif // DEBUG

	m_states.push(new States::MainMenuState(*m_window, m_states, m_supported_fonts, m_supported_keys));

#ifdef DEBUG
	std::cout << "\nGame: init_states is success!" << std::endl;
#endif // DEBUG
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
void Game::updateInfo()
{
	m_tech_info.str(std::string()); //Clearing

	m_tech_info << "Delta time: " << m_delta_time << " sec" << '\n';
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
	while (m_window->pollEvent(m_sf_event))
	{
		if (m_sf_event.type == sf::Event::Closed)
			m_window->close();

		if (m_sf_event.type == sf::Event::KeyPressed)
		{
			if (m_sf_event.key.code == (sf::Keyboard::Key(m_supported_keys["F3"])))
			{
				if (m_enable_info)
					m_enable_info = false;
				else
					m_enable_info = true;
			}
		}
	}
}

void Game::update()
{
	updateEvents();
	updateInfo();

	if (!m_states.empty())
	{
		//Update the top state
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
		m_window->draw(getTextInfo(*m_supported_fonts["DOSIS"]));

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