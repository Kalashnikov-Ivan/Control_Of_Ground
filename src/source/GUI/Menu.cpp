#include "stdafx.h"

#include "Menu.hpp"

using namespace GUI;

// Constructors
Menu::Menu(sf::Font& mainFont, sf::Vector2f bg_size)
	: sf::RectangleShape{ bg_size  }
	, m_mainFont		{ mainFont }
{
}

Menu::~Menu()
{
	DeleteButtons();
}

//Accessors
const bool Menu::IsButtonPressed(const std::string key)
{
	return m_buttons[key]->IsPressed();
}

//Modificators
void Menu::AddButton(const std::string key,
				const sf::Vector2f& pos, const sf::Vector2f& size_wh,
				sf::Font& font, const std::string& text, uint32_t chSize,
				const sf::Color& color_idle,
				const sf::Color& color_hover,
				const sf::Color& color_active)
{
	m_buttons[key] = new GUI::Button{ pos, size_wh, font, text, chSize,
									  color_idle,
									  color_hover,
									  color_active };
}

//Support_cleaner
void Menu::DeleteButtons()
{
	for (auto& i : m_buttons)
		delete i.second;
}

// Info
std::string Menu::GetStringInfo()
{
	std::stringstream result;

	for (auto& i : m_buttons)
		if (i.second->GetState() == Button::States::HOVER)
			result << i.second->SetStringInfo();

	return result.str();
}

// Update
void Menu::UpdateButtons(const sf::Vector2f& mousePos, const float& dt)
{
	for (auto& i : m_buttons)
		i.second->Update(mousePos, dt);
}

// Render
void Menu::RenderButtons(sf::RenderTarget& target)
{
	for (auto& i : m_buttons)
		i.second->Render(target);
}
