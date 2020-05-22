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
public:
	//Constructors
	MainMenuState() = delete;
	MainMenuState(sf::RenderWindow* window,
		std::map<const std::string, int>* supported_keys, std::stack<State*>* states);
	~MainMenuState();

	//Virtual override
	virtual void update_input(const float& dt) override; //Delete
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target = nullptr) override;

	void update_buttons(const float& dt);
	void render_buttons(sf::RenderTarget* target = nullptr);

private:
	//Members
	sf::RectangleShape m_background;
	sf::Font m_font;

	std::map<std::string, Button*> m_buttons;

	//Init
	virtual void init_textures() override;
	virtual void init_keybinds() override; //Delete
	void init_background();
	void init_fonts();
	void init_buttons();

	//Support_cleaner
	void delete_buttons();

};
} // !namespace cog
#endif // !MAIN_MENU_H