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
public:
//Constructors
	SettingsState() = delete;
	SettingsState(StateContext& Sdata);
	virtual ~SettingsState();

//Tech info
	std::string GetStringInfo() override;

//Functions
	void Pause()   = delete;
	void Unpause() = delete;

//Update and Render
	void UpdateEvent(const sf::Event& event) override;
	void Update(const float& dt) override;

	void Render(sf::RenderTarget& target) override;

	void Reset(const sf::VideoMode& vm) override;
private:
//GUI
	GUI::SettingsMenu m_settingsMenu;
	std::shared_ptr<GUI::AnimatedBackground> m_background;
	sf::Text m_title;

//Init
	void inline InitTextures() override;
	void inline InitKeybinds() override; //Delete
	void inline InitBackground(const sf::VideoMode& vm);

//Functions
	void inline ResetSettingsAllStates();

//Update
	virtual void UpdateInput(const float& dt) override; //Delete
};
} // !namespace States
#endif // !SETTINGS_STATE_H