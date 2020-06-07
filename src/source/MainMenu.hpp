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
	MainMenu(sf::RenderWindow& window,
			 std::map<const std::string, sf::Font*>& supported_fonts);
	~MainMenu();

	//Update
	void update(const sf::Vector2f& mouse_pos_window);

	//Render
	void render(sf::RenderTarget& target);

private:
	virtual void inline initButtons()        override;
};
} // !namespace GUI
#endif // !MAIN_MENU_H