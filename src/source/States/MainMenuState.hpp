#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.hpp"

#include "GUI/AnimatedBackground.h"
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
	MainMenuState(StateData& Sdata);
	virtual ~MainMenuState();

	//Tech info
	virtual std::string getStringInfo() override;

	//Functions
	void pause()   = delete;
	void unpause() = delete;

	virtual void reset(const sf::VideoMode& vm) override;

	//Update
	virtual void updateEvent(const sf::Event& event) override;
	virtual void update(const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;
//__________________________PRIVATE_____________________________
private:
	//Members
	GUI::MainMenu m_main_menu;
	GUI::AnimatedBackground* m_background;

	sf::Text m_title;

	//---------------------------------------------
	//Init
	virtual void inline initTextures() override;
	virtual void inline initKeybinds() override; //Delete
	void inline initBackground(const sf::VideoMode& vm);

	//Update
	virtual void updateInput(const float& dt) override; //Delete
};
} // !namespace States
#endif // !MAIN_MENU_STATE_H