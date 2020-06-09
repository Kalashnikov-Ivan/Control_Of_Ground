#include "stdHeader.hpp"

#include "Menu.hpp"

using namespace GUI;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Menu::Menu(sf::RenderWindow& window,
		   sf::Font& main_font)
	: m_window       { window    },
	  m_main_font    { main_font }
{
}

Menu::~Menu()
{
	deleteButtons();
}

//Accessors
const bool Menu::isButtonPressed(const std::string key)
{
	return m_buttons[key]->isPressed();
}

//Modificators
void Menu::addButton(const std::string key,
				const sf::Vector2f& pos, const sf::Vector2f& size_wh,
				sf::Font& font, const std::string& text, uint32_t ch_size,
				const sf::Color& color_idle,
				const sf::Color& color_hover,
				const sf::Color& color_active)
{
	m_buttons[key] = new GUI::Button{ pos, size_wh, font, text, ch_size,
									  color_idle,
									  color_hover,
									  color_active };
}

//Support_cleaner
void Menu::deleteButtons()
{
	for (auto& i : m_buttons)
		delete i.second;
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
std::string Menu::getStringInfo()
{
	std::stringstream result;

	for (auto& i : m_buttons)
		if (i.second->getState() == Button::States::HOVER)
			result << i.second->getStringInfo();

	return result.str();
}

////////////////////////////////////////////////////////////
// Update
////////////////////////////////////////////////////////////
void Menu::updateButtons(const sf::Vector2f& mouse_pos, const float& dt)
{
	for (auto& i : m_buttons)
		i.second->update(mouse_pos, dt);
}

////////////////////////////////////////////////////////////
// Render
////////////////////////////////////////////////////////////
void Menu::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : m_buttons)
		i.second->render(target);
}
