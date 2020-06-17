#ifndef PAUSE_MENU_H
#define PAUSE_MENU_H

#include "Button.hpp"
#include "Menu.hpp"

namespace GUI
{
class PauseMenu :
	public Menu
{
public:
	//Constructors
	PauseMenu(const sf::VideoMode& vm, sf::Font& main_font,
			  std::map<const std::string, sf::Font*>& supported_fonts);
	~PauseMenu();

	//Update
	void update(const sf::Vector2f& mouse_pos, const float& dt);

	//Render
	void render(sf::RenderTarget& target);

private:
	//Members
	sf::RectangleShape m_background;

	sf::Text m_title;

	void initBackground(const sf::VideoMode& vm);
	virtual void initButtons(const sf::VideoMode& vm) override;

	//Update
	virtual void updateButtons(const sf::Vector2f& mouse_pos, const float& dt) override;
};
} // !namespace GUI
#endif // !PAUSE_MENU_H