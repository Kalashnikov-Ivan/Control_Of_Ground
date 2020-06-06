#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "stdHeader.hpp"

#include "Button.hpp"
#include "Menu.hpp"

namespace GUI
{
class PauseMenu :
	public Menu
{
public:
	//Constructors
	PauseMenu(sf::RenderWindow& window);
	~PauseMenu();

	//Update
	void update(const sf::Vector2f& mouse_pos_window);

	//Render
	void render(sf::RenderTarget& target);

private:
	//Members
	sf::RectangleShape m_container;

	virtual void initBackground() override;
	virtual void initButtons()	  override;

	//Update
	virtual void updateButtons(const sf::Vector2f& mouse_pos) override;
};
} // !namespace GUI
#endif // !PAUSE_MENU_H