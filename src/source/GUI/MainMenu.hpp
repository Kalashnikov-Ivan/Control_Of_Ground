#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "Menu.hpp"

namespace GUI
{
class MainMenu :
	public Menu
{
public:
	//Constructors
	MainMenu(const sf::VideoMode& vm, sf::Font& main_font);
	~MainMenu();

	//Functions
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) override;
	virtual void render(sf::RenderTarget& target) override;

	virtual void reset(const sf::VideoMode& vm) override;

private:
	virtual void inline initButtons(const sf::VideoMode& vm) override;
			void inline resetButtons(const sf::VideoMode& vm);
};
} // !namespace GUI
#endif // !MAIN_MENU_H