#ifndef STATE_H
#define STATE_H

namespace cog
{
class State //Abstract
{
public:
	//Constructors
	State(sf::RenderWindow* window, std::map<const std::string, int>* supported_keys);
	virtual ~State();

	//Functions
	const bool get_quit() const;
	virtual void check_for_quit();
	
	//Pure virtual
	virtual void update_input(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	virtual void end_state() = 0;

protected:
	sf::RenderWindow* m_window; //Main render target -> Game
	std::map<const std::string, int>* m_supported_keys; // -> Game
	std::map<const std::string, int> m_keybinds; // -> Inherit

	bool m_quit;

	//Resources
	std::vector<sf::Texture> m_testures;

	//Functions
	virtual void init_keybinds() = 0;

private:

};
} // !namespace cog
#endif // !STATE_H