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
	SideBar(const sf::Vector2f& pos, const sf::Vector2f& boundsSize, const float m_buttonHeight);
	~SideBar();

	//Accessors
	const Button& GetButton(const std::string& key);
	const bool IsButtonPressed(const std::string& key);

	//Modificators
	void AddButton(const std::string& key,
			sf::Font& font, const std::string& text,
			const sf::Color& color_idle,
			const sf::Color& color_hover,
			const sf::Color& color_active);

	//Functions
	void Update(const sf::Vector2f& mousePos, const float& dt);
	void Render(sf::RenderTarget& target);

	void Reset(const sf::Vector2f& pos, const sf::Vector2f& boundsSize, const float buttonHeight);
private:
	//Members
	//#TODO: Make smart_ptr
	std::map<std::string, Button*> m_buttons;

	float m_buttonHeight;
	size_t m_quant_buttons;

	void UpdateButtons(const sf::Vector2f& mousePos, const float& dt);
	void RenderButtons(sf::RenderTarget& target);
};
} //!namespace GUI
#endif // !SIDEBAR_H