#include "stdHeader.hpp"

#include "Game.hpp"

#define DEBUG

using namespace cog;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Game::Game()
{
	init_window(sf::VideoMode(800U, 600U));
	init_supported_keys();
	init_states();
}

Game::Game(const sf::VideoMode& video_mode, unsigned int framerate_limit) 
	: m_window{ new sf::RenderWindow(video_mode, "Control of Ground") }
{
	if (m_window == nullptr)
		throw std::runtime_error("Fault of init_window! Is bad alloc...");

	m_window->setFramerateLimit(framerate_limit);

	std::cout << "Init_window successful! Video mode: " << 800U << ", " << 600U << std::endl;
	std::cout << "Frame rate = " << framerate_limit << std::endl;
}

////////////////////////////////////////////////////////////
// Tech functions
////////////////////////////////////////////////////////////

//Init
void Game::init_window(const sf::VideoMode& video_mode, unsigned int framerate_limit)
{
#ifdef DEBUG
	std::cout << "Game: Start of init_window..." << std::endl;
#endif // DEBUG

	m_window = new sf::RenderWindow{ video_mode, "Control of Ground" };

	if (m_window == nullptr)
	{
		std::cerr << "Fault of init_window! Is nullptr..." << std::endl;
		throw std::runtime_error("Fault of init_window!Is nullptr...");
	}

	m_window->setFramerateLimit(framerate_limit);
	m_window->setVerticalSyncEnabled(false);

#ifdef DEBUG
	std::cout << "Init_window successful!\nVideo mode: " << video_mode.width << ", " << video_mode.height << std::endl;
	std::cout << "Frame rate = " << framerate_limit << "\n" << std::endl;
#endif // DEBUG
}

void Game::init_supported_keys()
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

void Game::init_states()
{
#ifdef DEBUG
	std::cout << "\nGame: Start of init_states..." << std::endl;
#endif // DEBUG

	m_states.push(new GameState(m_window, &m_supported_keys));

#ifdef DEBUG
	std::cout << "\nGame: init_states is success!" << std::endl;
#endif // DEBUG
}

////////////////////////////////////////////////////////////
// Update and render
////////////////////////////////////////////////////////////
void Game::update_delta_time()
{
	m_delta_time = m_delta_time_clock.restart().asSeconds();
}

// ^ Tech for update_delta_time ^
void Game::print_dt() //delta time
{
	system("cls");
	std::cout << "Delta time: " << m_delta_time << " sec" << std::endl;
}

void Game::update_sf_events()
{
	while (m_window->pollEvent(m_sf_event))
	{
		if (m_sf_event.type == sf::Event::Closed)
			m_window->close();
	}
}

void Game::update_game()
{
	update_sf_events();

	if (!m_states.empty())
	{
		m_states.top()->update(m_delta_time);

		if (m_states.top()->get_quit())
		{
			m_states.top()->end_state();
			delete m_states.top();
			m_states.pop();
		}
	}
	else //Application end
	{
		application_end();
		m_window->close();
	}
}

void Game::application_end()
{
	std::cout << "Application: Control of Ground is end..." << std::endl;
}

void Game::render()
{
	m_window->clear();

	if (!m_states.empty())
	{
		m_states.top()->render(m_window);
	}

	m_window->display();
}

Game::~Game()
{
	delete m_window;

	delete_states();
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

////////////////////////////////////////////////////////////
// Core
////////////////////////////////////////////////////////////
void Game::run()
{
	while (m_window->isOpen())
	{
		update_delta_time();
		//print_dt();

		update_game();
		render();
	}
}