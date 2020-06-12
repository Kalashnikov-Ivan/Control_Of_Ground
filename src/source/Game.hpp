#ifndef GAME_H
#define GAME_H

#include "Settings/SettingsContainer.h"
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
	//Settings
		Settings::SettingsContainer m_settings;

	//Window
		sf::RenderWindow*          m_window;

	//Supported keys
		std::map<const std::string, int> m_supported_keys;

	//Time
		sf::Clock m_delta_time_clock;
		float m_delta_time;

	//States
		std::stack<States::State*> m_states;

	//Fonts
		std::map<const std::string, sf::Font*> m_supported_fonts;

	//Info
		std::stringstream m_tech_info;
		bool m_enable_info;

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

////////////////////////////////////////////////////////////
// Tech functions
////////////////////////////////////////////////////////////
	//Support_cleaner
		void inline deleteStates();
		void inline deleteFonts();
};
} // !namespace cog
#endif // !GAME_H