#ifndef SETTINGS_MENU
#define SETTINGS_MENU

#include "stdHeader.hpp"

#include "Menu.hpp"
#include "DropDownList.hpp"

namespace GUI
{
class SettingsMenu : 
	public Menu
{
public:
	//Constructors
	SettingsMenu(sf::RenderWindow& window,
				 sf::Font& main_font);
	virtual ~SettingsMenu();


	//Update
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;

private:
	//Members
	DropDownList* m_video_modes;

	//Init
	virtual void initButtons() override;
};
}

#endif // !SETTINGS_MENU