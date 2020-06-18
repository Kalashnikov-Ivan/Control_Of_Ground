#include "stdHeader.hpp"

#include "Converter.h"

#include "SettingsMenu.hpp"

using namespace GUI;

////////////////////////////////////////////////////////////
// VideoSettingsMenu
////////////////////////////////////////////////////////////
SettingsMenu::VideoSettingsMenu::VideoSettingsMenu(const sf::VideoMode& vm, sf::Font& main_font, std::vector<sf::VideoMode>& video_modes)
	: Menu      { main_font, sf::Vector2f(
								Converter::calc(33.3f, vm.width),
								Converter::calc(50.f,  vm.height)
								) },
	m_video_modes       { video_modes }, 
	m_title             { "Video",  main_font, Converter::calcCharSize(50 , vm) },
	m_resolution_text   { "Resolution",  main_font, Converter::calcCharSize(75 , vm) },
	m_vsync_text        { "Vsync",       main_font, Converter::calcCharSize(75 , vm) },
	m_antialising_text  { "Antialising", main_font, Converter::calcCharSize(75 , vm) }
{
	const float default_position_x = Converter::calc(11.f, vm.width); // 150.f;
	const float default_position_y = Converter::calc(25.f, vm.height); // 350.f;

	setPosition(default_position_x, default_position_y);
	setFillColor(sf::Color(20, 20, 20, 200));

	const sf::Vector2f& bg_size = getSize();

	sf::Vector2f dropdown_elems_size = { Converter::calc(45.f, bg_size.x), Converter::calc(10.f, bg_size.y) };

	//Convert VideoModes to string
	std::vector<std::string> video_modes_str;// = { "1920x1080", "1600x900", "1280x1024", "1024x768", "800x600" }
	for (auto& i : m_video_modes)
		video_modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));

	m_dropdown_lists["RESOLUTION"] = new DropDownList(main_font, sf::Vector2f(
																	getPosition().x + Converter::calc(48.f, bg_size.x),
																	getPosition().y + Converter::calc(30.f, bg_size.y)
																	),
														dropdown_elems_size, Converter::calcCharSize(95, vm),
													    video_modes_str, 0);

	m_title.setLetterSpacing(3.5f);

	m_title.setPosition(
		getPosition().x + Converter::calc(50.f, bg_size.x) - m_title.getGlobalBounds().width / 2,
		getPosition().y + Converter::calc(12.f, bg_size.y) - m_title.getGlobalBounds().height / 2
	);

	m_resolution_text.setPosition(
		getPosition().x + Converter::calc(8.f, bg_size.x),
		getPosition().y + Converter::calc(32.f, bg_size.y)
		);

	m_vsync_text.setPosition(
		getPosition().x + Converter::calc(8.f, bg_size.x),
		getPosition().y + Converter::calc(47.f, bg_size.y)
	);

	m_antialising_text.setPosition(
		getPosition().x + Converter::calc(8.f, bg_size.x),
		getPosition().y + Converter::calc(62.f, bg_size.y)
	);
}

SettingsMenu::VideoSettingsMenu::~VideoSettingsMenu()
{
	//Delete DropDownLists
	for (auto& i : m_dropdown_lists)
		delete i.second;
}

//Info
std::string SettingsMenu::VideoSettingsMenu::getStringInfo()
{
	std::stringstream result;

	for (auto& i : m_dropdown_lists)
		result << i.second->getStringInfo();

	return result.str();
}

//Accessors
sf::VideoMode SettingsMenu::VideoSettingsMenu::getCurrentVM()
{
	return m_video_modes[m_dropdown_lists["RESOLUTION"]->getActiveElemIndex()];
}

void SettingsMenu::VideoSettingsMenu::initButtons(const sf::VideoMode& vm) //Delete
{
}

//Update
void inline SettingsMenu::VideoSettingsMenu::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	for (auto& i : m_dropdown_lists)
		i.second->update(mouse_pos, dt);
}
//Render
void SettingsMenu::VideoSettingsMenu::render(sf::RenderTarget& target)
{
	target.draw(*this);

	//DropDownLists
	for (auto& i : m_dropdown_lists)
		i.second->render(target);

	target.draw(m_title);
	target.draw(m_resolution_text);
	target.draw(m_vsync_text);
	target.draw(m_antialising_text);
}

void SettingsMenu::VideoSettingsMenu::reset(const sf::VideoMode& vm)
{
	setSize(sf::Vector2f(
		Converter::calc(33.3f, vm.width),
		Converter::calc(50.f, vm.height))
	);

	const float default_position_x = Converter::calc(11.f, vm.width); // 150.f;
	const float default_position_y = Converter::calc(25.f, vm.height); // 350.f;

	setPosition(default_position_x, default_position_y);

	const sf::Vector2f& bg_size = getSize();

	sf::Vector2f dropdown_elems_size = { Converter::calc(45.f, bg_size.x), Converter::calc(10.f, bg_size.y) };

	m_dropdown_lists["RESOLUTION"]->reset(dropdown_elems_size, 
		sf::Vector2f(getPosition().x + Converter::calc(48.f, bg_size.x), getPosition().y + Converter::calc(30.f, bg_size.y)),
		Converter::calcCharSize(95, vm)
	);

	m_title.setPosition(
		getPosition().x + Converter::calc(50.f, bg_size.x) - m_title.getGlobalBounds().width / 2,
		getPosition().y + Converter::calc(12.f, bg_size.y) - m_title.getGlobalBounds().height / 2
	);
	m_title.setCharacterSize(Converter::calcCharSize(50, vm));

	m_resolution_text.setPosition(
		getPosition().x + Converter::calc(8.f, bg_size.x),
		getPosition().y + Converter::calc(32.f, bg_size.y)
	);
	m_resolution_text.setCharacterSize(Converter::calcCharSize(75, vm));

	m_vsync_text.setPosition(
		getPosition().x + Converter::calc(8.f, bg_size.x),
		getPosition().y + Converter::calc(47.f, bg_size.y)
	);
	m_vsync_text.setCharacterSize(Converter::calcCharSize(75, vm));

	m_antialising_text.setPosition(
		getPosition().x + Converter::calc(8.f, bg_size.x),
		getPosition().y + Converter::calc(62.f, bg_size.y)
	);
	m_antialising_text.setCharacterSize(Converter::calcCharSize(75, vm));
}

//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------------------------
////////////////////////////////////////////////////////////
// SettingsMenu
////////////////////////////////////////////////////////////
SettingsMenu::SettingsMenu(const sf::VideoMode& vm, sf::Font& main_font, std::vector<sf::VideoMode>& video_modes)
	: Menu{ main_font },
	m_video_menu{ vm, main_font, video_modes }
{
	initButtons(vm);
}
SettingsMenu::~SettingsMenu()
{
}

//Accessors
sf::VideoMode SettingsMenu::getCurrentVM()
{
	return m_video_menu.getCurrentVM();
}

//Init
void SettingsMenu::initButtons(const sf::VideoMode& vm)
{
	unsigned int char_size = Converter::calcCharSize(95, vm); // 1600x900 = 26U

	const float button_width = Converter::calc(14.5f, vm.width); // 1600x900 = 230.f
	const float button_height = Converter::calc(9.5f, vm.height); // 1600x900 = 85.f

	const float default_position_x = Converter::calc(30.f, vm.width); // 150.f;
	const float default_position_y = Converter::calc(80.f, vm.height); // 350.f;
	const float default_offset_between = Converter::calc(25.f, vm.width); // 1600x900 = 120.f

	addButton("BACK", sf::Vector2f(default_position_x, default_position_y),
		sf::Vector2f(button_width, button_height),
		m_main_font, "Back", char_size,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));

	addButton("APPLY", sf::Vector2f(default_position_x + default_offset_between, default_position_y),
		sf::Vector2f(button_width, button_height),
		m_main_font, "Apply", char_size,
		sf::Color(105, 105, 105, 200), sf::Color(192, 192, 192, 255), sf::Color(20, 20, 20, 200));
}

//Info
std::string SettingsMenu::getStringInfo()
{
	std::stringstream result;

	result << Menu::getStringInfo();
	result << m_video_menu.getStringInfo();

	return result.str();
}

//Update
void SettingsMenu::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	updateButtons(mouse_pos, dt);
	m_video_menu.update(mouse_pos, dt);
}

//Render
void SettingsMenu::render(sf::RenderTarget& target)
{
	renderButtons(target);
	m_video_menu.render(target);
}

//Reset
void SettingsMenu::reset(const sf::VideoMode& vm)
{
	unsigned int char_size = Converter::calcCharSize(95, vm); // 1600x900 = 26U

	const float button_width = Converter::calc(14.5f, vm.width); // 1600x900 = 230.f
	const float button_height = Converter::calc(9.5f, vm.height); // 1600x900 = 85.f

	const float default_position_x = Converter::calc(30.f, vm.width); // 150.f;
	const float default_position_y = Converter::calc(80.f, vm.height); // 350.f;
	const float default_offset_between = Converter::calc(25.f, vm.width); // 1600x900 = 120.f

	m_buttons["BACK"]->reset(sf::Vector2f(button_width, button_height),
		sf::Vector2f(default_position_x, default_position_y),
		char_size
	);

	m_buttons["APPLY"]->reset(sf::Vector2f(button_width, button_height),
		sf::Vector2f(default_position_x + default_offset_between, default_position_y),
		char_size
	);

	m_video_menu.reset(vm);
}