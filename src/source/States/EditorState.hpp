#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.hpp"
#include "TileMap.hpp"

#include "GUI/Button.hpp"
#include "GUI/PauseMenu.hpp"

namespace States
{
class EditorState :
	public State
{
//__________________________PUBLIC______________________________
public:
	//Constructors
	EditorState(StateData& Sdata);
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
	TileMap m_tile_map;

	GUI::PauseMenu m_pause_menu;

	//---------------------------------------------
	//Init
	virtual void initTextures() override;
	virtual void initKeybinds() override;

	//Update
	void updatePauseInput(const float& dt);
	virtual void updateInput(const float& dt) override;

	//Render

	//Support_cleaner
};
} // !namespace States
#endif // !EDITOR_STATE_H