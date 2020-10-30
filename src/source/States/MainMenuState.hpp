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
public:
//Constructors
	MainMenuState() = delete;
	explicit MainMenuState(StateContext& Sdata);
	~MainMenuState();

//Tech info
	 std::string GetStringInfo() override;

//Functions
	void Pause()   = delete;
	void Unpause() = delete;

	void UpdateEvent(const sf::Event& event) override;
	void Update(const float& dt) override;

	void Render(sf::RenderTarget& target) override;

	void Reset(const sf::VideoMode& vm) override;
private:
//Members
	GUI::MainMenu m_mainMenu;
	std::shared_ptr<GUI::AnimatedBackground> m_background;

	sf::Text m_title;

//Init
	virtual void inline InitTextures() override;
	virtual void inline InitKeybinds() override; //Delete
	void inline InitBackground(const sf::VideoMode& vm);

//Update
	virtual void UpdateInput(const float& dt) override; //Delete
};
} // !namespace States
#endif // !MAIN_MENU_STATE_H