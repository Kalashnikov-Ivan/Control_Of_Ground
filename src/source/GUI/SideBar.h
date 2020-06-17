#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "Menu.hpp"

namespace GUI
{
class SideBar :
	public Menu
{
public:
	//Constructors
	SideBar(const sf::VideoMode& vm, sf::Font& main_font, const sf::Vector2f& pos,
			const sf::Vector2f& bounds_size, const sf::Vector2f& button_size);
	~SideBar();

	//Update
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;

private:
	sf::RectangleShape m_bounds;
	sf::Vector2f m_button_size;

	//Init
	virtual void initButtons(const sf::VideoMode& vm) override;
};
} //!namespace GUI
#endif // !SIDEBAR_H