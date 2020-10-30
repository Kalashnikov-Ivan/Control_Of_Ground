#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.hpp"
#include "Tiles/TileMap.hpp"

#include "GUI/Button.hpp"
#include "GUI/PauseMenu.hpp"
#include "GUI/TextureSelector.h"
#include "GUI/SideBar.h"

namespace States
{
class EditorState :
	public State
{
public:
//Constructors
	EditorState(StateContext& ctx, const float clickTime = 0.07f);
	~EditorState();

//Tech info
	std::string GetStringInfo() override;

//Functions
	void UpdateEvent(const sf::Event& event) override;
	void Update(const float& dt) override;

	void Render(sf::RenderTarget& target) override;

	void Reset(const sf::VideoMode& vm) override;

private:
	std::unique_ptr<Tiles::TileMap> m_tileMap;

	GUI::PauseMenu m_pauseMenu;
	GUI::SideBar   m_sidebar;
	std::unique_ptr<GUI::TextureSelector> m_textureSelector;
	
	sf::RectangleShape m_selector;
	sf::IntRect m_selectedRect;

//Timer
	const float m_clickTime;
	float		m_timer;

//Init
	virtual void InitTextures() override;
	virtual void InitKeybinds() override;

//Update
	void UpdatePauseInput(const float& dt);
	void UpdateInput(const float& dt) override;

//Timer
	void UpdateTimer(const float& dt);
	bool IsTime();

//Render

//Support_cleaner
};
} // !namespace States
#endif // !EDITOR_STATE_H