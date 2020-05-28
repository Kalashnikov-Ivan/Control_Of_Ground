#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "State.hpp"
#include "GameState.hpp"
#include "Button.hpp"

namespace cog
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
	virtual std::string get_string_info() override;

	//Update
	virtual void update(const float& dt) override;

	//Render
	virtual void render(sf::RenderTarget* target = nullptr) override;
//__________________________PRIVATE_____________________________
private:
	//Members
	sf::RectangleShape m_background;
	std::map<std::string, Button*> m_buttons;
	sf::Text m_title;

	//---------------------------------------------
	//Init
	void inline init_background();
	void inline init_buttons();

	virtual void init_textures() override;
	virtual void init_keybinds() override; //Delete

	//Update
	virtual void update_keyboard_input(const float& dt) override; //Delete
			void update_buttons(const float& dt);

	//Render
	void render_buttons(sf::RenderTarget* target = nullptr);

	//Support_cleaner
	void delete_buttons();
};
} // !namespace cog
#endif // !MAIN_MENU_H