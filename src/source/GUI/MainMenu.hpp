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
	MainMenu(const sf::VideoMode& vm, sf::Font& mainFont);
	~MainMenu();

	//Functions
	virtual void Update(const sf::Vector2f& mousePos, const float& dt) override;
	virtual void Render(sf::RenderTarget& target) override;

	virtual void Reset(const sf::VideoMode& vm) override;

private:
	virtual void inline InitButtons(const sf::VideoMode& vm) override;
			void inline ResetButtons(const sf::VideoMode& vm);
};
} // !namespace GUI
#endif // !MAIN_MENU_H