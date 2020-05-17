#ifndef GAME_H
#define GAME_H

namespace cog
{
class State;

class Game final
{
public:
	//Constructors
	Game();
	Game(const sf::VideoMode& video_mode, unsigned int framerate_limit = 120U);
	~Game();

	//Init
	bool init_window(const sf::VideoMode& video_mode, unsigned int framerate_limit = 120U);
	bool init_states();

	//Core
	void run();

private:
	//Window, event
	sf::RenderWindow* m_window;
	sf::Event m_sf_event;

	//Time
	sf::Clock m_delta_time_clock;
	float m_delta_time;

	//States
	std::stack<State*> m_states;

	//Update
	void update_delta_time();
	void update_sf_events();
	void update_game();

	void application_end();

	//Render
	void render();

	//Print tech
	void print_dt(); //delta time and frame rate
};
} // !namespace my
#endif // !GAME_H