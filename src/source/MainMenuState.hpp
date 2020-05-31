#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "State.hpp"
#include "GameState.hpp"
#include "Button.hpp"

namespace States
{
class MainMenuState :
	public State
{
//__________________________PUBLIC______________________________
public:
	//Constructors
	MainMenuState() = delete;
	MainMenuState(sf::RenderWindow& window,
				  std::stack<State*>& states,
				  std::map<const std::string, sf::Font*>& supported_fonts,
				  const std::map<const std::string, int>& supported_keys);
	~MainMenuState();

	//Tech info
	virtual std::string getStringInfo() override;

	//Update
	virtual void update(const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget& target) override;
//__________________________PRIVATE_____________________________
private:
	//Members
	sf::RectangleShape m_background;
	std::map<std::string, Core::Button*> m_buttons;
	sf::Text m_title;

	//---------------------------------------------
	//Init
	void inline initBackground();
	void inline initButtons();

	virtual void initTextures() override;
	virtual void initKeybinds() override; //Delete

	//Update
	virtual void updateKeyboardInput(const float& dt) override; //Delete
			void updateButtons(const float& dt);

	//Render
	void renderButtons(sf::RenderTarget& target);

	//Support_cleaner
	void deleteButtons();
};
} // !namespace cog
#endif // !MAIN_MENU_H