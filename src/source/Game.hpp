#ifndef GAME_H
#define GAME_H

namespace cog
{
class Game
{
public:
	bool init_window(const sf::VideoMode& video_mode, unsigned int framerate_limit = 120U);

	//Constructors and Destructor
	Game();
	Game(const sf::VideoMode& video_mode, unsigned int framerate_limit = 120U);
	virtual ~Game();

	//Core
	void run();

private:
	sf::RenderWindow* const m_window;
	sf::Event m_sf_event;

	sf::Clock m_delta_time_clock;
	float m_delta_time;

	//Update
	void update_delta_time();
	void update_sf_events();
	void update_state();

	//Render
	void render();

	//Print tech
	void print_dt(); //delta time and frame rate
};
} // !namespace my

#endif // !GAME_H