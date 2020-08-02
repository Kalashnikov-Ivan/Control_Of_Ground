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
	void run();

private:
////////////////////////////////////////////////////////////
// Members
////////////////////////////////////////////////////////////
	//General data
		std::unique_ptr<sf::RenderWindow> m_window;
		Settings::SettingsContainer		  m_settings;
		std::vector<std::unique_ptr<States::State>> m_states;

		std::map<const std::string, int> m_supported_keys;
		std::map<const std::string, std::unique_ptr<sf::Font>> m_supported_fonts;

	//All values
		std::unique_ptr<States::StateData> m_Sdata;

	//Time
		sf::Clock m_delta_time_clock;
		float	  m_delta_time;

	//Info
		std::stringstream m_tech_info;
		std::stringstream m_mouse_info;
		bool              m_enable_info;

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
	void inline initSettings();
	void inline initWindow();
	void inline initSupportedKeys();
	void inline initSupportedFonts();
	void inline initFirstState();

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
	void updateInfo();
	sf::Text getTextInfo(const sf::Font& font);
	sf::Text getMouseTextInfo(const sf::Font& font);

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
	//Update
		void inline updateEvents();
		void inline updateDeltaTime();
		void inline update();

		void inline applicationEnd();

	//Render
		void inline render();
};
} // !namespace cog
#endif // !GAME_H