#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.hpp"
#include "GUI/Button.hpp"

namespace States
{
class EditorState :
	public State
{
//__________________________PUBLIC______________________________
public:
	//Constructors
	EditorState(GeneralValues& ref_GV);
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


	//---------------------------------------------
	//Init
	virtual void initTextures() override;
	virtual void initKeybinds() override;

	//Update
	virtual void updateInput(const float& dt) override;

	//Render

	//Support_cleaner
};
} // !namespace States
#endif // !EDITOR_STATE_H