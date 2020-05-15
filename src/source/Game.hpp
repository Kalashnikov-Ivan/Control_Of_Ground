#ifndef GAME_H
#define GAME_H

namespace cog
{
class Game
{
public:
	bool init_window(const sf::VideoMode& video_mode, unsigned int frame_rate = 60U);

	//Constructors and Destructor
	Game();
	Game(const sf::VideoMode& video_mode, unsigned int frame_rate = 60U);
	virtual ~Game();



	//Core
	void run();

private:
	sf::RenderWindow* m_window;

};
} //namespace my

#endif // !GAME_H