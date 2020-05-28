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
// Members
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
	std::map<const std::string, sf::Font*> m_supported_fonts;

	//Info
	std::stringstream m_tech_info;

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
	void inline init_window();
	void inline init_supported_keys();
	void inline init_supported_fonts();
	void inline init_states();

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
	//Update
	void inline update_delta_time();
	void inline update_sf_events();
	void inline update_game();

	void inline application_end();

	//Render
	void inline render();

////////////////////////////////////////////////////////////
// Tech functions
////////////////////////////////////////////////////////////
	//Info
	void inline update_info();
	sf::Text get_text_info(const sf::Font& font);

	std::string get_string_dt();
	sf::Text get_text_dt(const sf::Font& font); //delta time and frame rate

	//Support_cleaner
	void inline delete_states();
	void inline delete_fonts();
};
} // !namespace cog
#endif // !GAME_H