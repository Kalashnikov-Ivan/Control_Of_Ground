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
	SettingsMenu(const sf::VideoMode& vm, sf::Font& main_font, std::vector<sf::VideoMode>& video_modes);
	virtual ~SettingsMenu();

	//Accessors
	sf::VideoMode getCurrentVM();

	//Info
	virtual std::string getStringInfo() override;

	//Functions
	virtual void update(const sf::Vector2f& mouse_pos, const float& dt) override;
	virtual void render(sf::RenderTarget& target) override;

	virtual void reset(const sf::VideoMode& vm) override;

private:
	class VideoSettingsMenu :
		public Menu
	{
	public:
		VideoSettingsMenu(const sf::VideoMode& vm, sf::Font& main_font, std::vector<sf::VideoMode>& video_modes);
		~VideoSettingsMenu();

		//Accessors
		sf::VideoMode getCurrentVM();

		//Info
		std::string getStringInfo();

		//Functions
		void inline update(const sf::Vector2f& mouse_pos, const float& dt);
		void render(sf::RenderTarget& target);

		virtual void reset(const sf::VideoMode& vm) override;

	private:
		sf::Text m_title;

		//GUI
		std::map<std::string, DropDownList*> m_dropdown_lists;

		std::vector<sf::VideoMode>& m_video_modes;
		sf::Text m_resolution_text;
		sf::Text m_vsync_text;
		sf::Text m_antialising_text;

		virtual void initButtons(const sf::VideoMode& vm) override; //Delete
	};

	//Sub Menu
	VideoSettingsMenu m_video_menu;

	//Init
	virtual void inline initButtons(const sf::VideoMode& vm) override;
};
}

#endif // !SETTINGS_MENU