#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "stdHeader.hpp"

#include "State.hpp"
#include "GUI/MainMenu.hpp"

namespace States
{
class MainMenuState :
	public State
{
//__________________________PUBLIC______________________________
public:
	//Constructors
	MainMenuState() = delete;
	MainMenuState(sf::RenderWindow& window,
				  std::stack<State*>& states,
				  std::map<const std::string, sf::Font*>& supported_fonts,
				  const std::map<const std::string, int>& supported_keys);
	virtual ~MainMenuState();

	//Tech info
	virtual std::string getStringInfo() override;

	//Functions
	void pause()   = delete;
	void unpause() = delete;

	//Update
	virtual void update(const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;
//__________________________PRIVATE_____________________________
private:
	//Members
	GUI::MainMenu m_main_menu;
	sf::RectangleShape m_background;
	sf::Text m_title;

	//---------------------------------------------
	//Init
	virtual void inline initTextures() override;
	virtual void inline initKeybinds() override; //Delete
	void inline initBackground();

	//Update
	virtual	void updateEvents() override;
	virtual void updateInput(const float& dt) override; //Delete
};
} // !namespace States
#endif // !MAIN_MENU_STATE_H