#include "stdHeader.hpp"

#include "Game.hpp"

using namespace cog;

/*
bool Game::init_window(const sf::VideoMode& video_mode, unsigned int framerate_limit = 60U)
{
	m_window = new sf::RenderWindow{ video_mode, "Control of Ground" };

	if (m_window == nullptr)
	{
		std::cerr << "Fault of init_window! Is nullptr..." << std::endl;
		return false;
	}

	m_window->setFramerateLimit(framerate_limit);

	std::cout << "Init_window successful! Video mode: " << video_mode.width << ", " << video_mode.height << std::endl;
	std::cout << "Frame rate = " << frame_rate << std::endl;
	return true;
}
*/


////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Game::Game() : m_window { new sf::RenderWindow(sf::VideoMode(800U, 600U), "Control of Ground")}
{
	if (m_window == nullptr)
		throw std::runtime_error("Fault of init_window! Is bad alloc...");

	unsigned int frame_rate = 120U;

	m_window->setFramerateLimit(frame_rate);
	m_window->setVerticalSyncEnabled(false);

	std::cout << "Init_window successful! Video mode: " << 800U << ", " << 600U << std::endl;
	std::cout << "Frame rate = " << frame_rate << std::endl;
	//init_window(sf::VideoMode(800U, 600U));
}

Game::Game(const sf::VideoMode& video_mode, unsigned int framerate_limit) :
	m_window{ new sf::RenderWindow(video_mode, "Control of Ground") }
{
	if (m_window == nullptr)
		throw std::runtime_error("Fault of init_window! Is bad alloc...");

	m_window->setFramerateLimit(framerate_limit);

	std::cout << "Init_window successful! Video mode: " << 800U << ", " << 600U << std::endl;
	std::cout << "Frame rate = " << framerate_limit << std::endl;
}

Game::~Game()
{
	delete m_window;
}

////////////////////////////////////////////////////////////
// Core
////////////////////////////////////////////////////////////
void Game::run()
{
	while (m_window->isOpen())
	{
		update_delta_time();
		print_dt();

		update_state();
		render();
	}
}

////////////////////////////////////////////////////////////
// Update and render
////////////////////////////////////////////////////////////
void Game::update_delta_time()
{
	m_delta_time = m_delta_time_clock.restart().asSeconds();
}

void Game::update_sf_events()
{
	while (m_window->pollEvent(m_sf_event))
	{
		if (m_sf_event.type == sf::Event::Closed)
			m_window->close();
	}
}

void Game::update_state()
{
	update_sf_events();
}

void Game::render()
{
	m_window->clear();

	m_window->display();
}

void Game::print_dt() //delta time and frame rate
{
	system("cls");
	std::cout << "Delta time: " << m_delta_time << " sec" << std::endl;
}