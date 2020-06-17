#include "stdHeader.hpp"

#include "Converter.h"

#include "PauseMenu.hpp"

using namespace GUI;

//Constructors
PauseMenu::PauseMenu(const sf::VideoMode& vm, sf::Font& main_font,
					 std::map<const std::string, sf::Font*>& supported_fonts)
	: Menu            { main_font, sf::Vector2f(
										Converter::calc(22.f , vm.width),
										static_cast<float>(vm.height)
										) 
					  },
	m_background      { sf::Vector2f(vm.width, vm.height) },
	m_title           { "paused", *supported_fonts["MAJOR"],  Converter::calcCharSize(45, vm) }
{
	initBackground(vm);
	initButtons(vm);
}

PauseMenu::~PauseMenu()
{

}

//Init
void PauseMenu::initBackground(const sf::VideoMode& vm)
{
	//Background
	m_background.setFillColor(sf::Color(20, 20, 20, 100));

	setFillColor(sf::Color(20, 20, 20, 200));
	setPosition(Converter::calc(50.f ,vm.width) - (getSize().x / 2.f), 0.f);

	//Title
	m_title.setStyle(sf::Text::Bold);

	const float default_position_x = GUI::Converter::calc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float default_position_y = GUI::Converter::calc(9.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(default_position_x, default_position_y);
}

void PauseMenu::initButtons(const sf::VideoMode& vm)
{
	unsigned int font_size = Converter::calcCharSize(95, vm); // 1600x900 = 26U

	const float button_width = Converter::calc(14.5f, vm.width); // 1600x900 = 230.f
	const float button_height = Converter::calc(9.5f, vm.height); // 1600x900 = 85.f

	const float default_position_x = Converter::calc(50.f, vm.width) - (button_width / 2.f); // 150.f;
	const float default_position_y = Converter::calc(40.f, vm.height) - (button_height / 2.f); // 350.f;
	const float default_offset_between = Converter::calc(14.f, vm.height); // 1600x900 = 120.f

	addButton("SETTINGS_STATE", sf::Vector2f(default_position_x, default_position_y * 1.5f),
		sf::Vector2f(button_width, button_height),
		m_main_font, "Settings", font_size,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));


	addButton("EXIT", sf::Vector2f(default_position_x, default_position_y * 2.2f),
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
	target.draw(*this);
	target.draw(m_title);

	renderButtons(target);
}