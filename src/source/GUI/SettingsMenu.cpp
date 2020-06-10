#include "stdHeader.hpp"

#include "SettingsMenu.hpp"

using namespace GUI;

////////////////////////////////////////////////////////////
// VideoSettingsMenu
////////////////////////////////////////////////////////////
SettingsMenu::VideoSettingsMenu::VideoSettingsMenu(sf::RenderWindow& window,
												   sf::Font& main_font)
	: m_video_modes{ nullptr },
	m_background{ sf::Vector2f(window.getSize().x / 3.f, window.getSize().y / 2.f) },
	m_resolution_text{ "Resolution", main_font, 32U },
	m_vsync_text{ "Vsync", main_font, 32U }
{
	const float background_width = m_background.getSize().x;
	const float background_height = m_background.getSize().y;

	const float default_position_x = (window.getSize().x / 4.f) - (background_width / 2.f); // 150.f;
	const float default_position_y = (window.getSize().y / 2.f) - (background_height / 2.f); // 350.f;

	m_background.setPosition(default_position_x, default_position_y);
	m_background.setFillColor(sf::Color(20, 20, 20, 200));

	m_rp = m_background.getPosition();
	const sf::Vector2f& bg_size = m_background.getSize();

	std::string list[] = { "1920x1080", "1280x1024", "800x600" };

	sf::Vector2f video_modes_size = { 230.f, 50.f };
	float center_x = video_modes_size.x / 2.f;
	float center_y = video_modes_size.y / 2.f;

	m_video_modes = new DropDownList(main_font, sf::Vector2f(
															  m_rp.x + ((bg_size.x / 6.f) * 4.f) - center_x,
															  m_rp.y + (bg_size.y / 6.f) - center_y
															),
									 video_modes_size, 26U,
									 list, 3, 0);

	center_x = m_resolution_text.getGlobalBounds().width / 2.f;
	center_y = m_resolution_text.getGlobalBounds().height / 2.f;

	m_resolution_text.setPosition(m_rp.x + (bg_size.x / 5.5f) - center_x,
								  m_rp.y + (bg_size.y / 6.f) - center_y);

	m_vsync_text.setPosition	 (m_rp.x + (bg_size.x / 5.5f) - center_x,
								  m_rp.y + ((bg_size.y / 6.f) * 2.f) - center_y);
}

SettingsMenu::VideoSettingsMenu::~VideoSettingsMenu()
{
	delete m_video_modes;
}

//Update
void inline SettingsMenu::VideoSettingsMenu::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	m_video_modes->update(mouse_pos, dt);
}
//Render
void SettingsMenu::VideoSettingsMenu::render(sf::RenderTarget& target)
{
	target.draw(m_background);
	m_video_modes->render(target);
	target.draw(m_resolution_text);
	target.draw(m_vsync_text);
}


////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
SettingsMenu::SettingsMenu(sf::RenderWindow& window,
						   sf::Font& main_font)
	: Menu{ window, main_font },
	m_video_menu{ window, main_font }
{
	initButtons();
}
SettingsMenu::~SettingsMenu()
{
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
	m_video_menu.update(mouse_pos, dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void SettingsMenu::render(sf::RenderTarget& target)
{
	renderButtons(target);
	m_video_menu.render(target);
}