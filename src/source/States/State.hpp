#ifndef STATE_H
#define STATE_H

#include "GUI/AnimatedBackground.h"
#include "Settings/SettingsContainer.h"

namespace States
{
class State;

class StateData
{
public:
	StateData(sf::RenderWindow& window, std::stack<States::State*>& states, Settings::SettingsContainer& settings,
			  std::map<const std::string, int>& supported_keys, std::map<const std::string, sf::Font*>& supported_fonts,
			  sf::Vector2f grid_size = sf::Vector2f(100.f, 100.f))
		: window{ window }, states{ states }, settings{ settings },
		supported_keys { supported_keys }, supported_fonts { supported_fonts },
		grid_size_f { grid_size }
	{}
	~StateData()
	{}

	sf::RenderWindow& window;
	sf::Vector2f grid_size_f;

	std::stack<States::State*>& states;

	Settings::SettingsContainer& settings;

	std::map<const std::string, int>&       supported_keys;
	std::map<const std::string, sf::Font*>& supported_fonts;

	//Shared objects
	GUI::AnimatedBackground* background_anim;
};

class State //Base
{
//__________________________PUBLIC______________________________
public:
	//Constructors
	State() = delete;
	State(StateData& sdata);

	virtual ~State();
	
	//Accessors
	const bool getQuit() const;

	//Info
	virtual std::string getStringInfo() = 0;
	virtual std::string getStringInfoMouse();
	std::string getStringMousePos() const;

	//Functions
	void pause();
	void unpause();
	virtual void reset(const sf::VideoMode& vm);
	virtual void quitState();

	//Update and render
	virtual void updateEvent(const sf::Event& event) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

//__________________________PROTECTED_____________________________
protected:
////////////////////////////////////////////////////////////
// Refs
////////////////////////////////////////////////////////////
	StateData& m_Sdata;

////////////////////////////////////////////////////////////
// Member
////////////////////////////////////////////////////////////
	//Resources
	std::map<const std::string, sf::Texture*> m_textures;

	std::map<const std::string, int> m_keybinds;

	//Mouse
	sf::Vector2i m_mouse_pos_screen;
	sf::Vector2i m_mouse_pos_window;
	sf::Vector2f m_mouse_pos_view;
	sf::Vector2u m_mouse_pos_grid;
	
	//State
	bool m_paused;
	bool m_quit;

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
	virtual void inline initTextures() = 0;
	virtual void inline initKeybinds() = 0;

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
	virtual void updateMousePos();
	virtual void updateInput(const float& dt) = 0;

//__________________________PRIVATE_____________________________
private:
	//Support_cleaner
	void deleteTextures();
};
} // !namespace States

#endif // !STATE_H