#ifndef SETTINGS_MENU
#define SETTINGS_MENU

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
	class VideoSettingsMenu
	{
	public:
		VideoSettingsMenu(sf::RenderWindow& window, 
						  sf::Font& main_font);
		~VideoSettingsMenu();

		//Update
		void inline update(const sf::Vector2f& mouse_pos, const float& dt);
		//Render
		void render(sf::RenderTarget& target);

	private:
		//Members
		sf::RectangleShape m_background;
		sf::Vector2f m_rp; //Relative point

		DropDownList* m_video_modes;

		sf::Text m_resolution_text;
		sf::Text m_vsync_text;
	};

	//Sub Menu
	VideoSettingsMenu m_video_menu;

	//Init
	virtual void inline initButtons() override;
};
}

#endif // !SETTINGS_MENU