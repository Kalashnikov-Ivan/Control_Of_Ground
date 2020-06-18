#ifndef MENU_H
#define MENU_H

#include "Button.hpp"

namespace GUI
{
class Menu :
	public sf::RectangleShape
{
public:
	//Constructors
	Menu(sf::Font& main_font, sf::Vector2f bg_size = sf::Vector2f(0.f, 0.f));
	virtual ~Menu();

	//Accessors
	const bool isButtonPressed(const std::string key);

	//Modificators
	void addButton(const std::string key,
				   const sf::Vector2f& pos, const sf::Vector2f& size_wh,
				   sf::Font& font, const std::string& text, uint32_t ch_size,
				   const sf::Color& color_idle,
				   const sf::Color& color_hover,
				   const sf::Color& color_active);

	//Info
	virtual std::string getStringInfo();

	//Functions
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;

	virtual void reset(const sf::VideoMode& vm) = 0;

//__________________________PROTECTED_____________________________
protected:
	sf::Font& m_main_font;

	//Members
	std::map<std::string, Button*> m_buttons;
	
//---------------------------------------------
	//Init
	virtual void initButtons(const sf::VideoMode& vm) = 0;

	//Update
	virtual void updateButtons(const sf::Vector2f& mouse_pos, const float& dt);

	//Render
	void renderButtons(sf::RenderTarget& target);

private:
	//Support_cleaner
	void deleteButtons();
};
} // !namespace GUI
#endif // !MENU_H