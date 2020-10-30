#include "stdafx.h"

#include "Converter.h"

#include "MainMenu.hpp"

using namespace GUI;

// Constructors
MainMenu::MainMenu(const sf::VideoMode& vm, sf::Font& mainFont)
	: Menu { mainFont }
{
	InitButtons(vm);
}
MainMenu::~MainMenu()
{
}

// Init
void MainMenu::InitButtons(const sf::VideoMode& vm)
{
	unsigned int fontSize = Converter::СalcCharSize(95, vm); // 1600x900 = 26U

	const float buttonWidth = Converter::Сalc(14.5f, vm.width); // 1600x900 = 230.f
	const float buttonHeight = Converter::Сalc(9.5f, vm.height); // 1600x900 = 85.f

	const float defaultPosition_x = Converter::Сalc(50.f, vm.width) - (buttonWidth / 2.f); // 150.f;
	const float defaultPosition_y = Converter::Сalc(40.f, vm.height) - (buttonHeight / 2.f); // 350.f;
	const float defaultOffsetBetween = Converter::Сalc(14.f, vm.height); // 1600x900 = 120.f

	AddButton("GAME_STATE",   sf::Vector2f(defaultPosition_x, defaultPosition_y),
							  sf::Vector2f(buttonWidth, buttonHeight),
							  m_mainFont, "New Game", fontSize,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	AddButton("EDITOR_STATE", sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween),
							  sf::Vector2f(buttonWidth, buttonHeight),
							  m_mainFont, "Editor", fontSize,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	AddButton("SETTINGS_STATE",     sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 2.f),
							  sf::Vector2f(buttonWidth, buttonHeight),
							  m_mainFont, "Settings", fontSize,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	AddButton("EXIT",   sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 3.5f),
							  sf::Vector2f(buttonWidth, buttonHeight),
							  m_mainFont, "Exit", fontSize,
							  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));
}

// Update
void MainMenu::Update(const sf::Vector2f& mousePos, const float& dt)
{
	UpdateButtons(mousePos, dt);
}

// Render
void MainMenu::Render(sf::RenderTarget& target)
{
	RenderButtons(target);
}

//Reset
inline void MainMenu::ResetButtons(const sf::VideoMode& vm)
{
	unsigned int fontSize = Converter::СalcCharSize(95, vm); // 1600x900 = 26U

	const float buttonWidth = Converter::Сalc(14.5f, vm.width); // 1600x900 = 230.f
	const float buttonHeight = Converter::Сalc(9.5f, vm.height); // 1600x900 = 85.f

	const float defaultPosition_x = Converter::Сalc(50.f, vm.width) - (buttonWidth / 2.f); // 150.f;
	const float defaultPosition_y = Converter::Сalc(40.f, vm.height) - (buttonHeight / 2.f); // 350.f;
	const float defaultOffsetBetween = Converter::Сalc(14.f, vm.height); // 1600x900 = 120.f

	m_buttons["GAME_STATE"]->Reset(sf::Vector2f(buttonWidth, buttonHeight),
		sf::Vector2f(defaultPosition_x, defaultPosition_y),
		fontSize
		);

	m_buttons["EDITOR_STATE"]->Reset(sf::Vector2f(buttonWidth, buttonHeight),
		sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween),
		fontSize
	);

	m_buttons["SETTINGS_STATE"]->Reset(sf::Vector2f(buttonWidth, buttonHeight),
		sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 2.f),
		fontSize
	);

	m_buttons["EXIT"]->Reset(sf::Vector2f(buttonWidth, buttonHeight),
		sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 3.5f),
		fontSize
	);
}

void MainMenu::Reset(const sf::VideoMode& vm)
{
	ResetButtons(vm);
}