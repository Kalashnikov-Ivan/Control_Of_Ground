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
	Menu(sf::Font& mainFont, sf::Vector2f bgSize = sf::Vector2f(0.f, 0.f));
	virtual ~Menu();

	//Accessors
	const bool IsButtonPressed(const std::string key);

	//Modificators
	virtual void AddButton(const std::string key,
				   const sf::Vector2f& pos, const sf::Vector2f& size_wh,
				   sf::Font& font, const std::string& text, uint32_t chSize,
				   const sf::Color& color_idle,
				   const sf::Color& color_hover,
				   const sf::Color& color_active);

	//Info
	virtual std::string GetStringInfo();

	//Functions
	virtual void Update(const sf::Vector2f& mousePos, const float& dt) = 0;
	virtual void Render(sf::RenderTarget& target) = 0;

	virtual void Reset(const sf::VideoMode& vm) = 0;

//__________________________PROTECTED_____________________________
protected:
	sf::Font& m_mainFont;

	//Members
	std::map<std::string, Button*> m_buttons;
	
//---------------------------------------------
	//Init
	virtual void InitButtons(const sf::VideoMode& vm) = 0;

	//Update
	virtual void UpdateButtons(const sf::Vector2f& mousePos, const float& dt);

	//Render
	void RenderButtons(sf::RenderTarget& target);

private:
	//Support_cleaner
	void DeleteButtons();
};
} // !namespace GUI
#endif // !MENU_H