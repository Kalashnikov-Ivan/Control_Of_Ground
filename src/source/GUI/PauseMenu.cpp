#include "PauseMenu.hpp"

using namespace GUI;

//Constructors
PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& main_font,
					 std::map<const std::string, sf::Font*>& supported_fonts)
	: Menu            { window, main_font },
	m_supported_fonts { supported_fonts },
	m_background      { static_cast<sf::Vector2f>(window.getSize()) },
	m_container       { 
					    sf::Vector2f(static_cast<float>(window.getSize().x) / 4.f, 
						             static_cast<float>(window.getSize().y)) 
				      },
	m_title           { "paused", *supported_fonts["MAJOR"], 48U }
{
	initBackground();
	initButtons();
}

PauseMenu::~PauseMenu()
{

}

//Init
void PauseMenu::initBackground()
{
	//Background
	m_background.setFillColor(sf::Color(20, 20, 20, 100));

	m_container.setFillColor(sf::Color(20, 20, 20, 200));
	m_container.setPosition((m_window.getSize().x / 2.f) - (m_container.getSize().x / 2.f), 0.f);

	//Title
	m_title.setStyle(sf::Text::Bold);

	const float default_position_x = (m_window.getSize().x / 2.f) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = (m_window.getSize().y / 2.f) - (m_title.getGlobalBounds().height / 2.f); // Center
	const float default_offset_y = -350.f;

	m_title.setPosition(default_position_x - 10, default_position_y + default_offset_y);
}

void PauseMenu::initButtons()
{
	unsigned int font_size = 26U;

	const float button_width = 230.f;
	const float button_height = 85.f;

	const float default_position_x = (m_window.getSize().x / 2.f) - (button_width / 2.f); // 150.f;
	const float default_position_y = (m_window.getSize().y / 2.5f) - (button_height / 2.f); // 350.f;
	const float default_offset_between = 120.f;

	addButton("EXIT", sf::Vector2f(default_position_x, default_position_y * 2.f),
					  sf::Vector2f(button_width, button_height),
					  m_main_font, "Exit", font_size,
					  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));
}

//Update
void PauseMenu::updateButtons(const sf::Vector2f& mouse_pos, const float& dt)
{
	Menu::updateButtons(mouse_pos, dt);
	/*...*/
}

void PauseMenu::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	updateButtons(mouse_pos, dt);
}

//Render
void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(m_background);
	target.draw(m_container);
	target.draw(m_title);

	renderButtons(target);
}