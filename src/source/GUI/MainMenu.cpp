#include "stdHeader.hpp"

#include "Converter.h"

#include "MainMenu.hpp"

using namespace GUI;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
MainMenu::MainMenu(const sf::VideoMode& vm, sf::Font& main_font)
	: Menu { main_font }
{
	initButtons(vm);
}
MainMenu::~MainMenu()
{
}

void MainMenu::reset(const sf::VideoMode& vm)
{
	resetButtons(vm);
}

////////////////////////////////////////////////////////////
// Init
////////////////////////////////////////////////////////////

void MainMenu::initButtons(const sf::VideoMode& vm)
{
	unsigned int font_size = Converter::calcCharSize(95, vm); // 1600x900 = 26U

	const float button_width = Converter::calc(14.5f, vm.width); // 1600x900 = 230.f
	const float button_height = Converter::calc(9.5f, vm.height); // 1600x900 = 85.f

	const float default_position_x = Converter::calc(50.f, vm.width) - (button_width / 2.f); // 150.f;
	const float default_position_y = Converter::calc(40.f, vm.height) - (button_height / 2.f); // 350.f;
	const float default_offset_between = Converter::calc(14.f, vm.height); // 1600x900 = 120.f

	addButton("GAME_STATE",   sf::Vector2f(default_position_x, default_position_y),
							  sf::Vector2f(button_width, button_height),
							  m_main_font, "New Game", font_size,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	addButton("EDITOR_STATE", sf::Vector2f(default_position_x, default_position_y + default_offset_between),
							  sf::Vector2f(button_width, button_height),
							  m_main_font, "Editor", font_size,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	addButton("SETTINGS_STATE",     sf::Vector2f(default_position_x, default_position_y + default_offset_between * 2.f),
							  sf::Vector2f(button_width, button_height),
							  m_main_font, "Settings", font_size,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	addButton("EXIT",   sf::Vector2f(default_position_x, default_position_y + default_offset_between * 3.5f),
							  sf::Vector2f(button_width, button_height),
							  m_main_font, "Exit", font_size,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));
}

inline void MainMenu::resetButtons(const sf::VideoMode& vm)
{
	unsigned int font_size = Converter::calcCharSize(95, vm); // 1600x900 = 26U

	const float button_width = Converter::calc(14.5f, vm.width); // 1600x900 = 230.f
	const float button_height = Converter::calc(9.5f, vm.height); // 1600x900 = 85.f

	const float default_position_x = Converter::calc(50.f, vm.width) - (button_width / 2.f); // 150.f;
	const float default_position_y = Converter::calc(40.f, vm.height) - (button_height / 2.f); // 350.f;
	const float default_offset_between = Converter::calc(14.f, vm.height); // 1600x900 = 120.f

	m_buttons["GAME_STATE"]->setPosition(sf::Vector2f(default_position_x, default_position_y));
	//m_buttons["GAME_STATE"]->setSize(sf::Vector2f(button_width, button_height));

	m_buttons["EDITOR_STATE"]->setPosition(sf::Vector2f(default_position_x, default_position_y + default_offset_between));
	//m_buttons["EDITOR_STATE"]->setSize(sf::Vector2f(button_width, button_height));

	m_buttons["SETTINGS_STATE"]->setPosition(sf::Vector2f(default_position_x, default_position_y + default_offset_between * 2.f));
	//m_buttons["SETTINGS_STATE"]->setSize(sf::Vector2f(button_width, button_height));

	m_buttons["EXIT"]->setPosition(sf::Vector2f(default_position_x, default_position_y + default_offset_between * 3.5f));
	//m_buttons["EXIT"]->setSize(sf::Vector2f(button_width, button_height));
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