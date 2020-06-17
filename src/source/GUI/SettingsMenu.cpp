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
	m_resolution_text   { "Resolution",  main_font, Converter::calcCharSize(75 , vm) },
	m_vsync_text        { "Vsync",       main_font, Converter::calcCharSize(75 , vm) },
	m_antialising_text  { "Antialising", main_font, Converter::calcCharSize(75 , vm) }
{
	const float background_width  = getSize().x;
	const float background_height = getSize().y;

	const float default_position_x = Converter::calc(25.f, vm.width) - (background_width / 2.f); // 150.f;
	const float default_position_y = Converter::calc(25.f, vm.width) - (background_height / 2.f); // 350.f;

	setPosition(default_position_x, default_position_y);
	setFillColor(sf::Color(20, 20, 20, 200));

	const sf::Vector2f& bg_size = getSize();

	sf::Vector2f video_modes_size = { 230.f, 50.f };
	float center_x = video_modes_size.x / 2.f;
	float center_y = video_modes_size.y / 2.f;

	//Convert VideoModes to string
	std::vector<std::string> video_modes_str;// = { "1920x1080", "1600x900", "1280x1024", "1024x768", "800x600" }
	for (auto& i : m_video_modes)
		video_modes_str.push_back(std::to_string(i.width) + 'x' + std::to_string(i.height));

	m_dropdown_lists["RESOLUTION"] = new DropDownList(main_font, sf::Vector2f(
														getPosition().x + ((bg_size.x / 6.f) * 4.f) - center_x,
														getPosition().y + (bg_size.y / 6.f) - center_y
														),
													  video_modes_size, 26U,
													  video_modes_str, 0);

	center_x = m_resolution_text.getGlobalBounds().width / 2.f;
	center_y = m_resolution_text.getGlobalBounds().height / 2.f;

	m_resolution_text.setPosition (getPosition().x + (bg_size.x / 5.5f) - center_x,
								   getPosition().y + (bg_size.y / 6.f) - center_y);

	m_vsync_text.setPosition	  (getPosition().x + (bg_size.x / 5.5f) - center_x,
							       getPosition().y + ((bg_size.y / 6.f) * 2.f) - center_y);

	m_antialising_text.setPosition(getPosition().x + (bg_size.x / 5.5f) - center_x,
								   getPosition().y + ((bg_size.y / 6.f) * 3.f) - center_y);
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

	target.draw(m_resolution_text);
	target.draw(m_vsync_text);
	target.draw(m_antialising_text);
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
	unsigned int font_size = 26U;

	const float button_width = 230.f;
	const float button_height = 85.f;

	const float default_position_x = (vm.width / 2.5f) - (button_width / 2.f); // 150.f;
	const float default_position_y = (vm.height / 2.5f) - (button_height / 2.f); // 350.f;
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