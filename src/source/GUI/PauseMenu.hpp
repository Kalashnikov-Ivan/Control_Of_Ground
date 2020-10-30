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
	PauseMenu(const sf::VideoMode& vm, sf::Font& mainFont,
			  std::map<const std::string, std::unique_ptr<sf::Font>>& supportedFonts);
	~PauseMenu();

	//Functions
	virtual void Update(const sf::Vector2f& mousePos, const float& dt) override;
	virtual void Render(sf::RenderTarget& target) override;

	virtual void Reset(const sf::VideoMode& vm) override;

private:
	//Members
	sf::RectangleShape m_background;

	sf::Text m_title;

	void InitBackground(const sf::VideoMode& vm);
	virtual void InitButtons(const sf::VideoMode& vm) override;

	//Update
	virtual void UpdateButtons(const sf::Vector2f& mousePos, const float& dt) override;
	void inline resetButtons(const sf::VideoMode& vm);
};
} // !namespace GUI
#endif // !PAUSE_MENU_H