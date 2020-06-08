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
	Menu(sf::RenderWindow& window, 
		 std::map<const std::string, sf::Font*>& supported_fonts);

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

	//Update
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) = 0;

	//Render
	virtual void render(sf::RenderTarget& target) = 0;

//__________________________PROTECTED_____________________________
protected:
	//Refs
	sf::RenderWindow& m_window; //Main render target <- Game
	std::map<const std::string, sf::Font*>& m_supported_fonts;

	//Members
	std::map<std::string, Button*> m_buttons;
	
//---------------------------------------------
	//Init
	virtual void initButtons() = 0;

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