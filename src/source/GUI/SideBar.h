#ifndef SIDEBAR_H
#define SIDEBAR_H

#include "Button.hpp"

namespace GUI
{
class SideBar :
	public sf::RectangleShape
{
public:
	//Constructors
	SideBar(const sf::Vector2f& pos, const sf::Vector2f& bounds_size, const float m_button_height);
	~SideBar();

	//Accessors
	const bool isButtonPressed(const std::string key);

	//Modificators
	void addButton(const std::string key,
			sf::Font& font, const std::string& text,
			const sf::Color& color_idle,
			const sf::Color& color_hover,
			const sf::Color& color_active);

	//Functions
	void update(const sf::Vector2f& mouse_pos, const float& dt);
	void render(sf::RenderTarget& target);

	void reset(const sf::Vector2f& pos, const sf::Vector2f& bounds_size, const float button_height);
private:
	//Members
	std::map<std::string, Button*> m_buttons;

	float m_button_height;
	size_t m_quant_buttons;

	void updateButtons(const sf::Vector2f& mouse_pos, const float& dt);
	void renderButtons(sf::RenderTarget& target);
};
} //!namespace GUI
#endif // !SIDEBAR_H