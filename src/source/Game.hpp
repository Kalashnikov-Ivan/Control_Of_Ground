#ifndef GAME_H
#define GAME_H

#include "States/State.hpp"

namespace Core
{
class Game final
{
public:
//Constructors
	Game();
	~Game();

//Core
	void Run();

private:
//General data
	std::unique_ptr<sf::RenderWindow> m_window;
	Settings::SettingsContainer		  m_settings;

	std::vector<std::unique_ptr<States::State>> m_states;

	std::map<const std::string, int>   m_supportedKeys;
	std::map<const std::string, std::unique_ptr<sf::Font>> m_supportedFonts;

//All values
	std::unique_ptr<States::StateContext> m_stateContext;

//Time
	sf::Clock m_dtClock;
	float	  m_dt;

//Info
	bool              m_enableInfo;
	std::stringstream m_techInfo;
	std::stringstream m_mouseInfo;

// Init
	void inline InitSettings();
	void inline InitWindow();
	void inline InitSupportedKeys();
	void inline InitSupportedFonts();
	void inline InitFirstState();

// Info
	void     UpdateInfo();
	sf::Text GetTextInfo(const sf::Font& font);
	sf::Text GetMouseTextInfo(const sf::Font& font);

//Update
	void inline UpdateEvents();
	void inline UpdateDeltaTime();
	void inline Update();

	void inline ApplicationEnd();

//Render
	void inline Render();
};
} // !namespace Core
#endif // !GAME_H