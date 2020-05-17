#ifndef STATE_H
#define STATE_H

namespace cog
{
class State
{
public:
	//Constructors
	State(sf::RenderWindow* window);
	virtual ~State();

	//Functions
	const bool get_quit() const;

	virtual void check_for_quit();
	
	//Pure virtual
	virtual void update_key_binds(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	virtual void end_state() = 0;

private:
	sf::RenderWindow* m_window; //Main render target
	std::vector<sf::Texture> m_testures;
	bool m_quit;
};
} // !namespace cog
#endif // !STATE_H