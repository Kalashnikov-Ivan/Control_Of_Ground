#ifndef STATE_H
#define STATE_H

namespace cog
{
class State //Abstract
{
public:
	//Constructors
	State() = delete;
	State(sf::RenderWindow* window, 
		std::map<const std::string, int>* supported_keys, std::stack<State*>* states);
	virtual ~State();

	//Functions
	const bool get_quit() const;
	virtual void check_for_quit();

	virtual void update_mouse_pos();
	sf::Text get_mouse_pos_text(const sf::Font& font) const;
	
	//Pure virtual
	virtual void update_input(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	virtual void end_state() = 0;

protected:
	sf::RenderWindow* m_window; //Main render target <- Game
	std::stack<State*>* m_states; //Global stack of states <- Game
	std::map<const std::string, int>* m_supported_keys; // <- Game
	std::map<const std::string, int> m_keybinds; // -> Inherit

	//Mouse
	sf::Vector2i m_mouse_pos_screen;
	sf::Vector2i m_mouse_pos_window;
	sf::Vector2f m_mouse_pos_view;
	
	bool m_quit;

	//Resources
	std::map<const std::string, sf::Texture*> m_textures;

	//Functions
	virtual void init_keybinds() = 0;

private:
	//Support_cleaner
	void delete_textures();
};
} // !namespace cog
#endif // !STATE_H