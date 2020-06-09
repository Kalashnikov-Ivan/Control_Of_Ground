#include "MainMenu.hpp"

using namespace GUI;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenu::MainMenu(sf::RenderWindow& window,
				   sf::Font& main_font)
	: Menu { window, main_font }
{
	initButtons();
}
MainMenu::~MainMenu()
{

}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////

void MainMenu::initButtons()
{
	unsigned int font_size = 26U;

	const float button_width = 230.f;
	const float button_height = 85.f;

	const float default_position_x = (m_window.getSize().x / 2.f) - (button_width / 2.f); // 150.f;
	const float default_position_y = (m_window.getSize().y / 2.5f) - (button_height / 2.f); // 350.f;
	const float default_offset_between = 120.f;

	addButton("GAME_STATE",   sf::Vector2f(default_position_x, default_position_y),
							  sf::Vector2f(button_width, button_height),
							  m_main_font, "New Game", font_size,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	addButton("EDITOR_STATE", sf::Vector2f(default_position_x, default_position_y + default_offset_between),
							  sf::Vector2f(button_width, button_height),
							  m_main_font, "Editor", font_size,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	addButton("SETTINGS_STATE",     sf::Vector2f(default_position_x, default_position_y + default_offset_between * 2),
							  sf::Vector2f(button_width, button_height),
							  m_main_font, "Settings", font_size,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	addButton("EXIT",   sf::Vector2f(default_position_x, default_position_y + default_offset_between * 3.5f),
							  sf::Vector2f(button_width, button_height),
							  m_main_font, "Exit", font_size,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void MainMenu::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	updateButtons(mouse_pos, dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void MainMenu::render(sf::RenderTarget& target)
{
	renderButtons(target);
}