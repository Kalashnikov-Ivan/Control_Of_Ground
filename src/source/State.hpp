#ifndef STATE_H
#define STATE_H

namespace cog
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
	const bool get_quit() const;

	//Tech info
	virtual std::string get_string_info() = 0;
	sf::Text get_mouse_pos_text(const sf::Font& font) const;

	//Update
	virtual void update(const float& dt) = 0;

	//Render
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	virtual void end_state();

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
	virtual void init_textures() = 0;
	std::map<const std::string, sf::Texture*> m_textures;

	virtual void init_keybinds() = 0;
	std::map<const std::string, int> m_keybinds; // -> Inherit

	//Mouse
	sf::Vector2i m_mouse_pos_screen;
	sf::Vector2i m_mouse_pos_window;
	sf::Vector2f m_mouse_pos_view;
	
	bool m_quit;

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
	virtual void update_mouse_pos();
	virtual void update_keyboard_input(const float& dt) = 0;

//__________________________PRIVATE_____________________________
private:
	//Support_cleaner
	void delete_textures();
};
} // !namespace cog
#endif // !STATE_H