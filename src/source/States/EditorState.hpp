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
//__________________________PUBLIC______________________________
public:
	//Constructors
	EditorState(StateData& Sdata, const float click_time = 0.07f);
	virtual ~EditorState();

	//Tech info
	virtual std::string getStringInfo() override;

	//Update
	virtual void updateEvent(const sf::Event& event) override;
	virtual void update(const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;

//__________________________PRIVATE_____________________________
private:
	//Members
	Tiles::TileMap* m_tile_map;

	GUI::PauseMenu m_pause_menu;
	GUI::SideBar   m_sidebar;
	GUI::TextureSelector* m_texture_selector;
	
	sf::RectangleShape m_selector;
	sf::IntRect m_selected_rect;

	//Timer
	const float m_click_time;
	float m_timer;

	//---------------------------------------------
	//Init
	virtual void initTextures() override;
	virtual void initKeybinds() override;

	//Update
	void updatePauseInput(const float& dt);
	virtual void updateInput(const float& dt) override;
	//Timer
	void updateTimer(const float& dt);
	bool isTime();

	//Render

	//Support_cleaner
};
} // !namespace States
#endif // !EDITOR_STATE_H