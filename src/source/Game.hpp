#ifndef GAME_H
#define GAME_H

#include "GeneralValues.h"
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
	//All values
		GeneralValues m_GV;

	//States
		std::stack<States::State*> m_states;

	//Time
		sf::Clock m_delta_time_clock;
		float m_delta_time;

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