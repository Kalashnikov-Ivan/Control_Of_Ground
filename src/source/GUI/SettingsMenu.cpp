#include "stdafx.h"

#include "Converter.h"

#include "SettingsMenu.hpp"

using namespace GUI;

////////////////////////////////////////////////////////////
// VideoSettingsMenu
////////////////////////////////////////////////////////////
SettingsMenu::VideoSettingsMenu::VideoSettingsMenu(const sf::VideoMode& vm, sf::Font& mainFont, std::vector<sf::VideoMode>& videoModes)
	: Menu      { mainFont, sf::Vector2f(
								Converter::Сalc(33.3f, vm.width),
								Converter::Сalc(50.f,  vm.height)) }
	, m_videoModes      { videoModes }
	, m_title           { "Video",  mainFont, Converter::СalcCharSize(50 , vm) }
	, m_resolutionText { "Resolution",  mainFont, Converter::СalcCharSize(75 , vm) }
	, m_vsyncText      { "Vsync",       mainFont, Converter::СalcCharSize(75 , vm) }
	, m_antialisingText{ "Antialising", mainFont, Converter::СalcCharSize(75 , vm) }
{
	const float defaultPosition_x = Converter::Сalc(11.f, vm.width); // 150.f;
	const float defaultPosition_y = Converter::Сalc(25.f, vm.height); // 350.f;

	setPosition(defaultPosition_x, defaultPosition_y);
	setFillColor(sf::Color(20, 20, 20, 200));

	const sf::Vector2f& bg_size = getSize();

	sf::Vector2f dropdown_elems_size = { Converter::Сalc(45.f, bg_size.x), Converter::Сalc(10.f, bg_size.y) };

	//Convert VideoModes to string
	std::vector<std::string> videoModes_str;// = { "1920x1080", "1600x900", "1280x1024", "1024x768", "800x600" }
	for (auto& i : m_videoModes)
		videoModes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));

	m_dropdownLists["RESOLUTION"] = new DropDownList(mainFont, sf::Vector2f(
																	getPosition().x + Converter::Сalc(48.f, bg_size.x),
																	getPosition().y + Converter::Сalc(30.f, bg_size.y)
																	),
														dropdown_elems_size, Converter::СalcCharSize(95, vm),
													    videoModes_str, 0);

	m_title.setLetterSpacing(3.5f);

	m_title.setPosition(
		getPosition().x + Converter::Сalc(50.f, bg_size.x) - m_title.getGlobalBounds().width / 2,
		getPosition().y + Converter::Сalc(12.f, bg_size.y) - m_title.getGlobalBounds().height / 2
	);

	m_resolutionText.setPosition(
		getPosition().x + Converter::Сalc(8.f, bg_size.x),
		getPosition().y + Converter::Сalc(32.f, bg_size.y)
		);

	m_vsyncText.setPosition(
		getPosition().x + Converter::Сalc(8.f, bg_size.x),
		getPosition().y + Converter::Сalc(47.f, bg_size.y)
	);

	m_antialisingText.setPosition(
		getPosition().x + Converter::Сalc(8.f, bg_size.x),
		getPosition().y + Converter::Сalc(62.f, bg_size.y)
	);
}

SettingsMenu::VideoSettingsMenu::~VideoSettingsMenu()
{
	//Delete DropDownLists
	for (auto& i : m_dropdownLists)
		delete i.second;
}

//Info
std::string SettingsMenu::VideoSettingsMenu::GetStringInfo()
{
	std::stringstream result;

	for (auto& i : m_dropdownLists)
		result << i.second->GetStringInfo();

	return result.str();
}

//Accessors
sf::VideoMode SettingsMenu::VideoSettingsMenu::GetCurrentVM()
{
	return m_videoModes[m_dropdownLists["RESOLUTION"]->GetActiveElemIndex()];
}

void SettingsMenu::VideoSettingsMenu::InitButtons(const sf::VideoMode& vm) //Delete
{
}

//Update
void inline SettingsMenu::VideoSettingsMenu::Update(const sf::Vector2f& mousePos, const float& dt)
{
	for (auto& i : m_dropdownLists)
		i.second->Update(mousePos, dt);
}
//Render
void SettingsMenu::VideoSettingsMenu::Render(sf::RenderTarget& target)
{
	target.draw(*this);

	//DropDownLists
	for (auto& i : m_dropdownLists)
		i.second->Render(target);

	target.draw(m_title);
	target.draw(m_resolutionText);
	target.draw(m_vsyncText);
	target.draw(m_antialisingText);
}

void SettingsMenu::VideoSettingsMenu::Reset(const sf::VideoMode& vm)
{
	setSize(sf::Vector2f(
		Converter::Сalc(33.3f, vm.width),
		Converter::Сalc(50.f, vm.height))
	);

	const float defaultPosition_x = Converter::Сalc(11.f, vm.width); // 150.f;
	const float defaultPosition_y = Converter::Сalc(25.f, vm.height); // 350.f;

	setPosition(defaultPosition_x, defaultPosition_y);

	const sf::Vector2f& bg_size = getSize();

	sf::Vector2f dropdownElemsSize = { Converter::Сalc(45.f, bg_size.x), Converter::Сalc(10.f, bg_size.y) };

	m_dropdownLists["RESOLUTION"]->Reset(dropdownElemsSize, 
		sf::Vector2f(getPosition().x + Converter::Сalc(48.f, bg_size.x), getPosition().y + Converter::Сalc(30.f, bg_size.y)),
		Converter::СalcCharSize(95, vm)
	);

	m_title.setPosition(
		getPosition().x + Converter::Сalc(50.f, bg_size.x) - m_title.getGlobalBounds().width / 2,
		getPosition().y + Converter::Сalc(12.f, bg_size.y) - m_title.getGlobalBounds().height / 2
	);
	m_title.setCharacterSize(Converter::СalcCharSize(50, vm));

	m_resolutionText.setPosition(
		getPosition().x + Converter::Сalc(8.f, bg_size.x),
		getPosition().y + Converter::Сalc(32.f, bg_size.y)
	);
	m_resolutionText.setCharacterSize(Converter::СalcCharSize(75, vm));

	m_vsyncText.setPosition(
		getPosition().x + Converter::Сalc(8.f, bg_size.x),
		getPosition().y + Converter::Сalc(47.f, bg_size.y)
	);
	m_vsyncText.setCharacterSize(Converter::СalcCharSize(75, vm));

	m_antialisingText.setPosition(
		getPosition().x + Converter::Сalc(8.f, bg_size.x),
		getPosition().y + Converter::Сalc(62.f, bg_size.y)
	);
	m_antialisingText.setCharacterSize(Converter::СalcCharSize(75, vm));
}

////////////////////////////////////////////////////////////
// SettingsMenu
////////////////////////////////////////////////////////////
SettingsMenu::SettingsMenu(const sf::VideoMode& vm, sf::Font& mainFont, std::vector<sf::VideoMode>& videoModes)
	: Menu       { mainFont }
	, m_videoMenu{ vm, mainFont, videoModes }
{
	InitButtons(vm);
}
SettingsMenu::~SettingsMenu()
{
}

//Accessors
sf::VideoMode SettingsMenu::GetCurrentVM()
{
	return m_videoMenu.GetCurrentVM();
}

//Init
void SettingsMenu::InitButtons(const sf::VideoMode& vm)
{
	unsigned int charSize = Converter::СalcCharSize(95, vm); // 1600x900 = 26U

	const float buttonWidth = Converter::Сalc(14.5f, vm.width); // 1600x900 = 230.f
	const float buttonHeight = Converter::Сalc(9.5f, vm.height); // 1600x900 = 85.f

	const float defaultPosition_x = Converter::Сalc(30.f, vm.width); // 150.f;
	const float defaultPosition_y = Converter::Сalc(80.f, vm.height); // 350.f;
	const float defaultOffsetBetween = Converter::Сalc(25.f, vm.width); // 1600x900 = 120.f

	AddButton("BACK", sf::Vector2f(defaultPosition_x, defaultPosition_y),
		sf::Vector2f(buttonWidth, buttonHeight),
		m_mainFont, "Back", charSize,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	AddButton("APPLY", sf::Vector2f(defaultPosition_x + defaultOffsetBetween, defaultPosition_y),
		sf::Vector2f(buttonWidth, buttonHeight),
		m_mainFont, "Apply", charSize,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));
}

//Info
std::string SettingsMenu::GetStringInfo()
{
	std::stringstream result;

	result << Menu::GetStringInfo();
	result << m_videoMenu.GetStringInfo();

	return result.str();
}

//Update
void SettingsMenu::Update(const sf::Vector2f& mousePos, const float& dt)
{
	UpdateButtons(mousePos, dt);
	m_videoMenu.Update(mousePos, dt);
}

//Render
void SettingsMenu::Render(sf::RenderTarget& target)
{
	RenderButtons(target);
	m_videoMenu.Render(target);
}

//Reset
void SettingsMenu::Reset(const sf::VideoMode& vm)
{
	unsigned int charSize = Converter::СalcCharSize(95, vm); // 1600x900 = 26U

	const float buttonWidth = Converter::Сalc(14.5f, vm.width); // 1600x900 = 230.f
	const float buttonHeight = Converter::Сalc(9.5f, vm.height); // 1600x900 = 85.f

	const float defaultPosition_x = Converter::Сalc(30.f, vm.width); // 150.f;
	const float defaultPosition_y = Converter::Сalc(80.f, vm.height); // 350.f;
	const float defaultOffsetBetween = Converter::Сalc(25.f, vm.width); // 1600x900 = 120.f

	m_buttons["BACK"]->Reset(sf::Vector2f(buttonWidth, buttonHeight),
		sf::Vector2f(defaultPosition_x, defaultPosition_y),
		charSize
	);

	m_buttons["APPLY"]->Reset(sf::Vector2f(buttonWidth, buttonHeight),
		sf::Vector2f(defaultPosition_x + defaultOffsetBetween, defaultPosition_y),
		charSize
	);

	m_videoMenu.Reset(vm);
}