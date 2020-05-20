#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "State.hpp"

namespace cog
{
class MainMenuState :
	public State
{
public:
	MainMenuState(sf::RenderWindow* window, std::map<const std::string, int>* supported_keys);
	~MainMenuState();

	//Virtual override
	virtual void update_input(const float& dt) override;
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;

	virtual void end_state() override;

private:
	sf::RectangleShape m_background;

	virtual void init_keybinds() override;
};
} // !namespace cog
#endif // !MAIN_MENU_H