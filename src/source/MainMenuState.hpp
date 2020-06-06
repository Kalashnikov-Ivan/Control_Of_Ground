#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "stdHeader.hpp"

#include "Menu.hpp"
#include "State.hpp"
#include "Button.hpp"

namespace States
{
class MainMenuState :
	public State, public GUI::Menu
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
	sf::Text m_title;

	//---------------------------------------------
	//Init
	virtual void inline initTextures() override;
	virtual void inline initKeybinds() override; //Delete

	virtual void inline initBackground()     override;
	virtual void inline initButtons()        override;

	//Update
	virtual void updateInput(const float& dt) override; //Delete
	virtual	void updateButtons(const sf::Vector2f& mouse_pos) override;
};
} // !namespace cog
#endif // !MAIN_MENU_H