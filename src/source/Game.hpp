#ifndef GAME_H
#define GAME_H

#include "State.hpp"
#include "GameState.hpp"

namespace cog
{
class Game final
{
public:
	//Constructors
	Game();
	~Game();

	//Core
	void run();

private:
////////////////////////////////////////////////////////////
// Property objects
////////////////////////////////////////////////////////////
	//Window
	sf::RenderWindow*          m_window;
	sf::ContextSettings        m_window_settings;
	std::vector<sf::VideoMode> m_video_modes;
	bool m_fullscreen_enabled;

	sf::Event                  m_sf_event;

	//All supported keys
	std::map<const std::string, int> m_supported_keys;

	//Time
	sf::Clock m_delta_time_clock;
	float m_delta_time;

	//States
	std::stack<State*> m_states;

	//Fonts
	std::map<const std::string, sf::Font*> m_fonts;

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
	void init_window();
	void init_supported_keys();
	void init_fonts();
	void init_states();

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
	//Update
	void update_delta_time();
	void update_sf_events();
	void update_game();

	void application_end();

	//Render
	void render();

////////////////////////////////////////////////////////////
// Tech functions
////////////////////////////////////////////////////////////
	//Print tech
	void print_dt(); //delta time and frame rate

	//Support_cleaner
	void delete_states();
};
} // !namespace my
#endif // !GAME_H