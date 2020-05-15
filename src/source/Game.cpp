#include "stdHeader.hpp"

#include "Game.hpp"

using namespace cog;

bool Game::init_window(const sf::VideoMode& video_mode, unsigned int frame_rate = 60U)
{
	m_window = new sf::RenderWindow{ video_mode, "Control of Ground" };

	if (m_window == nullptr)
	{
		std::cerr << "Fault of init_window! Is nullptr..." << std::endl;
		return false;
	}

	m_window->setFramerateLimit(frame_rate);

	std::cout << "Init_window successful! Video mode: " << video_mode.width << ", " << video_mode.height << std::endl;
	std::cout << "Frame rate = " << frame_rate << std::endl;
	return true;
}

Game::Game() : m_window { new sf::RenderWindow(sf::VideoMode(800U, 600U), "Control of Ground")}
{
	if (m_window == nullptr)
		throw std::runtime_error("Fault of init_window! Is bad alloc...");

	unsigned int frame_rate = 60U;

	m_window->setFramerateLimit(frame_rate);

	std::cout << "Init_window successful! Video mode: " << 800U << ", " << 600U << std::endl;
	std::cout << "Frame rate = " << frame_rate << std::endl;
	//init_window(sf::VideoMode(800U, 600U));
}


Game::Game(const sf::VideoMode& video_mode, unsigned int frame_rate = 60U) :
	m_window{ new sf::RenderWindow(video_mode, "Control of Ground") }
{
	if (m_window == nullptr)
		throw std::runtime_error("Fault of init_window! Is bad alloc...");

	m_window->setFramerateLimit(frame_rate);

	std::cout << "Init_window successful! Video mode: " << 800U << ", " << 600U << std::endl;
	std::cout << "Frame rate = " << frame_rate << std::endl;
}


Game::~Game()
{
	delete m_window;
}