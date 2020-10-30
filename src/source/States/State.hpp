#ifndef STATE_H
#define STATE_H

#include "GUI/AnimatedBackground.h"
#include "Settings/SettingsContainer.h"

namespace States
{
class State;

struct StateContext
{
	StateContext(
		sf::RenderWindow& window,
		std::vector<std::unique_ptr<States::State>>& states,
		Settings::SettingsContainer& settings,
		std::map<const std::string, int>& supportedKeys,
		std::map<const std::string, std::unique_ptr<sf::Font>>& supportedFonts,
		sf::Vector2f gridSize = sf::Vector2f(100.f, 100.f)
	)
		: window{ window }
		, states{ states }
		, settings{ settings }
		, supportedKeys{ supportedKeys }
		, supportedFonts{ supportedFonts }
		, gridSze{ gridSize }
		, backgroundAnim{ nullptr }
	{}

	sf::RenderWindow& window;
	sf::Vector2f      gridSze;

	std::vector<std::unique_ptr<States::State>>& states;

	Settings::SettingsContainer& settings;

	std::map<const std::string, int>& supportedKeys;
	std::map<const std::string, std::unique_ptr<sf::Font>>& supportedFonts;

	//Shared objects
	std::shared_ptr<GUI::AnimatedBackground> backgroundAnim;
};

class State //Base
{
public:
//Constructors
	State() = delete;
	explicit State(StateContext& sdata);

	virtual ~State();
	
//Accessors
	const bool GetQuit() const;

//Info
	virtual std::string GetStringInfo() = 0;
	virtual std::string GetStringInfoMouse();
	std::string GetStringMousePos() const;

//Functions
	void Pause();
	void Unpause();
	virtual void Reset(const sf::VideoMode& vm);
	virtual void QuitState();

//Update and Render
	virtual void UpdateEvent(const sf::Event& event) = 0;
	virtual void Update(const float& dt)			 = 0;
	virtual void Render(sf::RenderTarget& target)    = 0;

protected:
	StateContext& m_stateContext;

//Resources
	std::map<const std::string, std::shared_ptr<sf::Texture>> m_textures;

	std::map<const std::string, int> m_keybinds;

//Mouse
	sf::Vector2i m_mousePosScreen;
	sf::Vector2i m_mousePosWindow;
	sf::Vector2f m_mousePosView;
	sf::Vector2u m_mousePosGrid;
	
//State
	bool m_paused;
	bool m_quit;

// Init
	virtual void inline InitTextures() = 0;
	virtual void inline InitKeybinds() = 0;

// Update
	virtual void UpdateMousePos();
	virtual void UpdateInput(const float& dt) = 0;
};
} // !namespace States

//#TODO: Make working alias
//using pState = std::unique_ptr<States::State>;
//using pFont  = std::unique_ptr<sf::Font>;

#endif // !STATE_H