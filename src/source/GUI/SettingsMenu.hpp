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
	SettingsMenu(const sf::VideoMode& vm, sf::Font& mainFont, std::vector<sf::VideoMode>& videoModes);
	~SettingsMenu();

	//Accessors
	sf::VideoMode GetCurrentVM();

	//Info
	std::string GetStringInfo() override;

	//Functions
	void Update(const sf::Vector2f& mousePos, const float& dt) override;
	void Render(sf::RenderTarget& target) override;

	void Reset(const sf::VideoMode& vm) override;

private:
	class VideoSettingsMenu :
		public Menu
	{
	public:
		VideoSettingsMenu(const sf::VideoMode& vm, sf::Font& mainFont, std::vector<sf::VideoMode>& videoModes);
		~VideoSettingsMenu();

		//Accessors
		sf::VideoMode GetCurrentVM();

		//Info
		std::string GetStringInfo();

		//Functions
		void inline Update(const sf::Vector2f& mousePos, const float& dt);
		void Render(sf::RenderTarget& target);

		virtual void Reset(const sf::VideoMode& vm) override;

	private:
		sf::Text m_title;

		//GUI
		std::map<std::string, DropDownList*> m_dropdownLists;

		std::vector<sf::VideoMode>& m_videoModes;
		sf::Text m_resolutionText;
		sf::Text m_vsyncText;
		sf::Text m_antialisingText;

		virtual void InitButtons(const sf::VideoMode& vm) override; //Delete
	};

	//Sub Menu
	VideoSettingsMenu m_videoMenu;

	//Init
	virtual void inline InitButtons(const sf::VideoMode& vm) override;
};
}

#endif // !SETTINGS_MENU