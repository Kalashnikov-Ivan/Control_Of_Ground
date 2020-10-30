#include "stdafx.h"

#include "Converter.h"

#include "SideBar.h"

using namespace GUI;

//Constructors
SideBar::SideBar(const sf::Vector2f& pos, const sf::Vector2f& boundsSize, const float buttonHeight)
	: sf::RectangleShape { boundsSize }
	, m_buttonHeight     { buttonHeight }
	, m_quant_buttons    { 0 }
{
	setFillColor(sf::Color(192, 192, 192, 100));
	setOutlineThickness(0.7f);
	setOutlineColor(sf::Color::White);

	setPosition(pos);
}

SideBar::~SideBar()
{
	//#TODO: Make smart_ptr
	for (auto& i : m_buttons)
		delete i.second;
}


//Accessors
const Button& SideBar::GetButton(const std::string& key)
{
	return *m_buttons[key];
}

const bool  SideBar::IsButtonPressed(const std::string& key)
{
	return m_buttons[key]->IsPressed();
}

//Modificators
void SideBar::AddButton(const std::string& key,
			sf::Font& font, const std::string& text,
			const sf::Color& color_idle,
			const sf::Color& color_hover,
			const sf::Color& color_active)
{
	uint32_t chSize = Converter::СalcCharSize(20, getSize());

	m_buttons[key] = new GUI::Button{ sf::Vector2f(getPosition().x, getPosition().y + (m_buttonHeight * m_quant_buttons)),
									  sf::Vector2f(getSize().x, m_buttonHeight),
									  font, text, chSize,
									  color_idle,
									  color_hover,
									  color_active };

	m_quant_buttons += 1;
}

//Update
void SideBar::UpdateButtons(const sf::Vector2f& mousePos, const float& dt)
{
	for (auto& i : m_buttons)
		i.second->Update(mousePos, dt);
}

void SideBar::Update(const sf::Vector2f& mousePos, const float& dt)
{
	UpdateButtons(mousePos, dt);
}


//Render
void SideBar::RenderButtons(sf::RenderTarget& target)
{
	for (auto& i : m_buttons)
		i.second->Render(target);
}

void SideBar::Render(sf::RenderTarget& target)
{
	target.draw(*this);

	RenderButtons(target);
}

void SideBar::Reset(const sf::Vector2f& pos, const sf::Vector2f& boundsSize, const float buttonHeight)
{
	setSize(boundsSize);
	setPosition(pos);

	int tmp = 0;
	for (auto& i : m_buttons)
	{
		i.second->Reset(sf::Vector2f(boundsSize.x, buttonHeight), 
			sf::Vector2f(getPosition().x, getPosition().y + (m_buttonHeight * tmp)), 
			Converter::СalcCharSize(20, getSize())
		);
		tmp += 1;
	}
}