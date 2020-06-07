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
	EditorState(sf::RenderWindow& window,
				std::stack<State*>& states,
				std::map<const std::string, sf::Font*>& supported_fonts,
				const std::map<const std::string, int>& supported_keys);
	virtual ~EditorState();

	//Tech info
	virtual std::string getStringInfo() override;

	//Update
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
	virtual	void updateEvents() override;
	virtual void updateInput(const float& dt) override;

	//Render

	//Support_cleaner
};
} // !namespace States
#endif // !EDITOR_STATE_H