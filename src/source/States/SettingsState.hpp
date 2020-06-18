#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include "State.hpp"

#include "GUI/AnimatedBackground.h"
#include "GUI/SettingsMenu.hpp"
#include "GUI/DropDownList.hpp"

namespace States
{
class SettingsState :
	public State
{
//__________________________PUBLIC______________________________
public:
	//Constructors
	SettingsState() = delete;
	SettingsState(StateData& Sdata);
	virtual ~SettingsState();

	//Tech info
	virtual std::string getStringInfo() override;

	//Functions
	void pause() = delete;
	void unpause() = delete;

	//Functions
	virtual void updateEvent(const sf::Event& event) override;
	virtual void update(const float& dt) override;

	virtual void render(sf::RenderTarget& target) override;

	virtual void reset(const sf::VideoMode& vm) override;
//__________________________PRIVATE_____________________________
private:
	//GUI
	GUI::SettingsMenu m_settings_menu;
	GUI::AnimatedBackground& m_background;
	sf::Text m_title;

	//---------------------------------------------
	//Init
	virtual void inline initTextures() override;
	virtual void inline initKeybinds() override; //Delete
	void inline initBackground(const sf::VideoMode& vm);

	//Functions
	void inline resetSettingsAllStates();

	//Update
	virtual void updateInput(const float& dt) override; //Delete
};
} // !namespace States
#endif // !SETTINGS_STATE_H