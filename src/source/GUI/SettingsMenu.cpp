#include "SettingsMenu.hpp"

using namespace GUI;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
SettingsMenu::SettingsMenu(sf::RenderWindow& window,
						   sf::Font& main_font)
	: Menu{ window, main_font },
	m_video_modes { nullptr }
{
	initButtons();

	std::string test_list[] = { "a1", "b2", "c3" };

	m_video_modes = new DropDownList(main_font, 
									sf::Vector2f(500.f, 500.f), sf::Vector2f(100.f, 100.f), 50U,
									test_list, 3, 0);
}
SettingsMenu::~SettingsMenu()
{
	delete m_video_modes;
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////

void SettingsMenu::initButtons()
{
	unsigned int font_size = 26U;

	const float button_width = 230.f;
	const float button_height = 85.f;

	const float default_position_x = (m_window.getSize().x / 2.5f) - (button_width / 2.f); // 150.f;
	const float default_position_y = (m_window.getSize().y / 2.5f) - (button_height / 2.f); // 350.f;
	const float default_offset_between = 120.f;

	addButton("APPLY", sf::Vector2f(default_position_x + 300.f, default_position_y + default_offset_between * 3.5f),
		sf::Vector2f(button_width, button_height),
		m_main_font, "Apply", font_size,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	addButton("BACK", sf::Vector2f(default_position_x, default_position_y + default_offset_between * 3.5f),
		sf::Vector2f(button_width, button_height),
		m_main_font, "Back", font_size,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void SettingsMenu::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	updateButtons(mouse_pos, dt);

	m_video_modes->update(mouse_pos, dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void SettingsMenu::render(sf::RenderTarget& target)
{
	renderButtons(target);

	m_video_modes->render(target);
}