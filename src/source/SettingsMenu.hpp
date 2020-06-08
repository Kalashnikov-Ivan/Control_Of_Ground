#ifndef SETTINGS_MENU
#define SETTINGS_MENU

#include "stdHeader.hpp"

#include "Menu.hpp"

namespace GUI
{
class SettingsMenu : 
	public Menu
{
public:
	//Constructors
	SettingsMenu(sf::RenderWindow& window,
				 std::map<const std::string, sf::Font*>& supported_fonts);
	virtual ~SettingsMenu();


	//Update
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;

private:
	//Init
	virtual void initButtons() override;
};
}

#endif // !SETTINGS_MENU