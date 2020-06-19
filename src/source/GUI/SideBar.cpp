#include "stdHeader.hpp"

#include "Converter.h"

#include "SideBar.h"

using namespace GUI;

//Constructors
SideBar::SideBar(const sf::Vector2f& pos, const sf::Vector2f& bounds_size, const float button_height)
	: sf::RectangleShape { bounds_size },
	m_button_height{ button_height }, m_quant_buttons { 0 }
{
	setFillColor(sf::Color(192, 192, 192, 100));
	setOutlineThickness(0.7f);
	setOutlineColor(sf::Color::White);

	setPosition(pos);
}

SideBar::~SideBar()
{
	for (auto& i : m_buttons)
		delete i.second;
}


//Accessors
const Button& SideBar::getButton(const std::string& key)
{
	return *m_buttons[key];
}

const bool  SideBar::isButtonPressed(const std::string& key)
{
	return m_buttons[key]->isPressed();
}

//Modificators
void SideBar::addButton(const std::string& key,
			sf::Font& font, const std::string& text,
			const sf::Color& color_idle,
			const sf::Color& color_hover,
			const sf::Color& color_active)
{
	uint32_t ch_size = Converter::calcCharSize(20, getSize());

	m_buttons[key] = new GUI::Button{ sf::Vector2f(getPosition().x, getPosition().y + (m_button_height * m_quant_buttons)),
									  sf::Vector2f(getSize().x, m_button_height),
									  font, text, ch_size,
									  color_idle,
									  color_hover,
									  color_active };

	m_quant_buttons += 1;
}

//Update
void SideBar::updateButtons(const sf::Vector2f& mouse_pos, const float& dt)
{
	for (auto& i : m_buttons)
		i.second->update(mouse_pos, dt);
}

void SideBar::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	updateButtons(mouse_pos, dt);
}


//Render
void SideBar::renderButtons(sf::RenderTarget& target)
{
	for (auto& i : m_buttons)
		i.second->render(target);
}

void SideBar::render(sf::RenderTarget& target)
{
	target.draw(*this);

	renderButtons(target);
}

void SideBar::reset(const sf::Vector2f& pos, const sf::Vector2f& bounds_size, const float button_height)
{
	setSize(bounds_size);
	setPosition(pos);

	int tmp = 0;
	for (auto& i : m_buttons)
	{
		i.second->reset(sf::Vector2f(bounds_size.x, button_height), 
			sf::Vector2f(getPosition().x, getPosition().y + (m_button_height * tmp)), 
			Converter::calcCharSize(20, getSize())
		);
		tmp += 1;
	}
}