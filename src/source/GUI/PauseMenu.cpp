#include "stdafx.h"

#include "Converter.h"

#include "PauseMenu.hpp"

using namespace GUI;

//Constructors
PauseMenu::PauseMenu(const sf::VideoMode& vm, sf::Font& mainFont,
					 std::map<const std::string, std::unique_ptr<sf::Font>>& supportedFonts)
	: Menu            { mainFont, sf::Vector2f(Converter::Сalc(22.f , vm.width), static_cast<float>(vm.height)) }
	, m_background    { sf::Vector2f((float)vm.width, (float)vm.height) }
	, m_title         { "paused", *supportedFonts["MAJOR"],  Converter::СalcCharSize(45, vm) }
{
	InitBackground(vm);
	InitButtons(vm);
}

PauseMenu::~PauseMenu()
{

}

//Init
void PauseMenu::InitBackground(const sf::VideoMode& vm)
{
	//Background
	m_background.setFillColor(sf::Color(20, 20, 20, 100));

	setFillColor(sf::Color(20, 20, 20, 200));
	setPosition(Converter::Сalc(50.f, vm.width) - (getSize().x / 2.f), 0.f);

	//Title
	m_title.setStyle(sf::Text::Bold);

	const float defaultPosition_x = GUI::Converter::Сalc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float defaultPosition_y = GUI::Converter::Сalc(9.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(defaultPosition_x, defaultPosition_y);
}

void PauseMenu::InitButtons(const sf::VideoMode& vm)
{
	unsigned int fontSize = Converter::СalcCharSize(95, vm); // 1600x900 = 26U

	const float buttonWidth = Converter::Сalc(14.5f, vm.width); // 1600x900 = 230.f
	const float buttonHeight = Converter::Сalc(9.5f, vm.height); // 1600x900 = 85.f

	const float defaultPosition_x = getPosition().x + Converter::Сalc(50.f, getSize().x) - (buttonWidth / 2.f); // 150.f;
	const float defaultPosition_y = getPosition().y + Converter::Сalc(15.f, getSize().y) - (buttonHeight / 2.f); // 350.f;
	const float defaultOffsetBetween = Converter::Сalc(12.f, getSize().y); // 1600x900 = 120.f

	AddButton("SAVE", sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 2.f),
		sf::Vector2f(buttonWidth, buttonHeight),
		m_mainFont, "Save", fontSize,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	AddButton("LOAD", sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 3.f),
		sf::Vector2f(buttonWidth, buttonHeight),
		m_mainFont, "Load", fontSize,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	AddButton("SETTINGS_STATE", sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 4.f),
		sf::Vector2f(buttonWidth, buttonHeight),
		m_mainFont, "Settings", fontSize,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));


	AddButton("EXIT", sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 6.f),
					  sf::Vector2f(buttonWidth, buttonHeight),
					  m_mainFont, "Exit", fontSize,
					  sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));
}

//Update
void PauseMenu::UpdateButtons(const sf::Vector2f& mousePos, const float& dt)
{
	Menu::UpdateButtons(mousePos, dt);
	/*...*/
}

void PauseMenu::Update(const sf::Vector2f& mousePos, const float& dt)
{
	UpdateButtons(mousePos, dt);
}

//Render
void PauseMenu::Render(sf::RenderTarget& target)
{
	target.draw(m_background);
	target.draw(*this);
	target.draw(m_title);

	RenderButtons(target);
}

void inline PauseMenu::resetButtons(const sf::VideoMode& vm)
{
	unsigned int fontSize = Converter::СalcCharSize(95, vm); // 1600x900 = 26U

	const float buttonWidth = Converter::Сalc(14.5f, vm.width); // 1600x900 = 230.f
	const float buttonHeight = Converter::Сalc(9.5f, vm.height); // 1600x900 = 85.f

	const float defaultPosition_x = getPosition().x + Converter::Сalc(50.f, getSize().x) - (buttonWidth / 2.f); // 150.f;
	const float defaultPosition_y = getPosition().y + Converter::Сalc(15.f, getSize().y) - (buttonHeight / 2.f); // 350.f;
	const float defaultOffsetBetween = Converter::Сalc(15.f, getSize().y); // 1600x900 = 120.f

	m_buttons["SETTINGS_STATE"]->Reset(sf::Vector2f(buttonWidth, buttonHeight),
		sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 3.f),
		fontSize
	);

	m_buttons["EXIT"]->Reset(sf::Vector2f(buttonWidth, buttonHeight),
		sf::Vector2f(defaultPosition_x, defaultPosition_y + defaultOffsetBetween * 4.5f),
		fontSize
	);
}

void PauseMenu::Reset(const sf::VideoMode& vm)
{
	setSize(sf::Vector2f(Converter::Сalc(22.f, vm.width), static_cast<float>(vm.height)));
	setPosition(Converter::Сalc(50.f, vm.width) - (getSize().x / 2.f), 0.f);

	m_background.setSize(sf::Vector2f((float)vm.width, (float)vm.height));

	//Title
	m_title.setCharacterSize(Converter::СalcCharSize(45, vm));
	const float defaultPosition_x = Converter::Сalc(49.f, vm.width) - (m_title.getGlobalBounds().width / 2.f); // Center
	const float defaultPosition_y = Converter::Сalc(9.f, vm.height) - (m_title.getGlobalBounds().height / 2.f); // Center

	m_title.setPosition(defaultPosition_x, defaultPosition_y);

	resetButtons(vm);
}