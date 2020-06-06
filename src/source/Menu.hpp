#ifndef MENU_H
#define MENU_H

#include "stdHeader.hpp"

#include "Button.hpp"

namespace GUI
{
class Menu
{
public:
	//Constructors
	Menu(sf::Vector2f background_size = sf::Vector2f(0.f,  0.f));
	virtual ~Menu();

	//Info
	virtual std::string getStringInfo();

//__________________________PROTECTED_____________________________
protected:
	//Members
	sf::RectangleShape m_background;
	std::map<std::string, Button*> m_buttons;

//---------------------------------------------
	//Init
	virtual void initBackground() = 0;
	virtual void initButtons()    = 0;

	//Update
	virtual void updateButtons(const sf::Vector2f& mouse_pos) = 0;

	//Render
	void renderButtons(sf::RenderTarget& target);

private:
	//Support_cleaner
	void deleteButtons();
};
} // !namespace GUI
#endif // !MENU_H