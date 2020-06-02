#ifndef STATE_H
#define STATE_H

namespace States
{
class State //Abstract
{
//__________________________PUBLIC______________________________
public:
	//Constructors
	State() = delete;
	State(sf::RenderWindow& window, 
		  std::stack<State*>& states,
		  std::map<const std::string, sf::Font*>& supported_fonts,
		  const std::map<const std::string, int>& supported_keys);
	virtual ~State();
	
	//Accessors
	const bool getQuit() const;

	//Info
	virtual std::string getStringInfo() = 0;
	std::string getStringMousePos() const;

	//Functions
	virtual void endState();

	//Update and render
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

//__________________________PROTECTED_____________________________
protected:
////////////////////////////////////////////////////////////
// Refs
////////////////////////////////////////////////////////////
	sf::RenderWindow& m_window; //Main render target <- Game
	std::stack<State*>& m_states; //Global stack of states <- Game

	std::map<const std::string, sf::Font*>& m_supported_fonts; // <- Game
	const std::map<const std::string, int>& m_supported_keys; // <- Game


////////////////////////////////////////////////////////////
// Member
////////////////////////////////////////////////////////////
	//Resources
	std::map<const std::string, sf::Texture*> m_textures;

	std::map<const std::string, int> m_keybinds; // -> Inherit

	//Mouse
	sf::Vector2i m_mouse_pos_screen;
	sf::Vector2i m_mouse_pos_window;
	sf::Vector2f m_mouse_pos_view;
	
	bool m_quit;

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////
	virtual void initTextures() = 0;
	virtual void initKeybinds() = 0;

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
	virtual void updateMousePos();
	virtual void updateKeyboardInput(const float& dt) = 0;

//__________________________PRIVATE_____________________________
private:
	//Support_cleaner
	void deleteTextures();
};
} // !namespace cog
#endif // !STATE_H