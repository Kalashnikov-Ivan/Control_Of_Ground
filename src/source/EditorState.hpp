#ifndef EDITOR_STATE_H
#define EDITOR_STATE_H

#include "State.hpp"
#include "Button.hpp"

namespace States
{
class EditorState :
	public State
{
//__________________________PUBLIC______________________________
public:
	//Constructors
	EditorState();
	~EditorState();

	//Tech info
	virtual std::string getStringInfo() override;

	//Update
	virtual void update(const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget* target = nullptr) override;

//__________________________PRIVATE_____________________________
private:
	//Members

	std::map<std::string, Core::Button*> m_buttons;

	//---------------------------------------------
	//Init
	void inline initButtons();

	virtual void initTextures() override;
	virtual void initKeybinds() override;

	//Update
	virtual void updateKeyboardInput(const float& dt) override;
	void updateButtons(const float& dt);

	//Render
	void renderButtons(sf::RenderTarget* target = nullptr);

	//Support_cleaner
	void deleteButtons();
};
} // !namespace States
#endif // !EDITOR_STATE_H