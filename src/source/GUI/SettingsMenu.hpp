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
	SettingsMenu(sf::RenderWindow& window, sf::Font& main_font, std::vector<sf::VideoMode>& video_modes);
	virtual ~SettingsMenu();

	//Accessors
	sf::VideoMode getCurrentVM();

	//Info
	virtual std::string getStringInfo() override;

	//Update
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;

private:
	class VideoSettingsMenu
	{
	public:
		VideoSettingsMenu(sf::RenderWindow& window, sf::Font& main_font, std::vector<sf::VideoMode>& video_modes);
		~VideoSettingsMenu();

		//Accessors
		sf::VideoMode getCurrentVM();

		//Info
		std::string getStringInfo();

		//Update
		void inline update(const sf::Vector2f& mouse_pos, const float& dt);
		//Render
		void render(sf::RenderTarget& target);

	private:
		//Members
		sf::RectangleShape m_background;
		sf::Vector2f m_rp; //Relative point

		//GUI
		std::map<std::string, DropDownList*> m_dropdown_lists;

		std::vector<sf::VideoMode>& m_video_modes;
		sf::Text m_resolution_text;
		sf::Text m_vsync_text;
		sf::Text m_antialising_text;
	};

	//Sub Menu
	VideoSettingsMenu m_video_menu;

	//Init
	virtual void inline initButtons() override;
};
}

#endif // !SETTINGS_MENU