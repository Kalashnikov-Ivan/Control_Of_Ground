#include "stdafx.h"

#include "Button.hpp"

using namespace GUI;

//Static members
float Button::m_pressTime { 0.f };

// Constructors
Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
	sf::Text& text,
	const sf::Color& color_idle,
	const sf::Color& color_hover,
	const sf::Color& color_active,
	const size_t index)
	: sf::RectangleShape{ size_wh }
	, m_text            { text }
	, m_color_idle      { color_idle }
	, m_color_hover     { color_hover }
	, m_color_active    { color_active }
	, m_state           { States::IDLE }
	, m_index           { index }
{
	sf::Transformable::setPosition(pos);
	setFillColor(m_color_idle);

	//Text by center
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f);

	m_text.setPosition(getPosition().x + getGlobalBounds().width / 2.f, getPosition().y + getGlobalBounds().height / 2.f);
}

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
			   sf::Font& font, const std::string& text, uint32_t chSize,
			   const sf::Color& color_idle, 
			   const sf::Color& color_hover,
			   const sf::Color& color_active,
			   const size_t index)
	: sf::RectangleShape { size_wh }
	, m_text         { text,  font, chSize }
	, m_color_idle   { color_idle   }
	, m_color_hover  { color_hover  }
	, m_color_active { color_active }
	, m_state        { States::IDLE }
	, m_index        { index }
{
	sf::Transformable::setPosition(pos);
	setFillColor(m_color_idle);

	//Text by center
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f);

	m_text.setPosition(getPosition().x + getGlobalBounds().width / 2.f, getPosition().y + getGlobalBounds().height / 2.f);
}
Button::~Button()
{

}

// Accessors
const Button::States Button::GetState() const
{
	return m_state;
}

const size_t Button::GetIndex() const
{
	return m_index;
}

const sf::Text Button::GetText() const
{
	return m_text;
}

const bool Button::IsPressed() const
{
	if (m_state == States::ACTIVE)
		return true;

	return false;
}

// Modificators
void Button::SetIndex(const size_t index)
{
	m_index = index;
}

void Button::SetPosition(const sf::Vector2f& pos)
{
	sf::Transformable::setPosition(pos);

	//Text by center
	m_text.setPosition(pos.x + getGlobalBounds().width / 2.f, pos.y + getGlobalBounds().height / 2.f);
}

void Button::SetText(const sf::Text& text)
{
	m_text = text;

	//Text by center
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f);

	m_text.setPosition(getPosition().x + getGlobalBounds().width / 2.f, getPosition().y + getGlobalBounds().height / 2.f);
}

void Button::SetTextString(const std::string& str)
{
	m_text.setString(str);
}

// Info
std::string Button::SetStringInfo() const
{
	std::stringstream result;

	result << "b_position x = " << getPosition().x << " " << "y = " << getPosition().y << '\n';
	result << "b_size x = "     << getSize().x << " " << "y = " << getSize().y << '\n';

	return result.str();
}

// Functions
void Button::UpdateTimer(const float& dt)
{
	m_pressTime += dt;
}

const bool Button::IsTime()
{
	if (m_pressTime >= m_maxPressTime)
	{
		m_pressTime = 0.f;
		return true;
	}

	return false;
}

void Button::Update(const sf::Vector2f& mousePos, const float& dt)
{
	/*Update the booleans for hover and pressed*/

	UpdateTimer(dt);
	m_state = States::IDLE;

	if (getGlobalBounds().contains(mousePos))
	{
		m_state = States::HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && IsTime())
			m_state = States::ACTIVE;
	}

	switch (m_state)
	{
	case States::IDLE:
		setFillColor(m_color_idle);
		break;
	case States::HOVER:
		setFillColor(m_color_hover);
		break;
	case States::ACTIVE:
		setFillColor(m_color_active);
		break;
	default:
		setFillColor(sf::Color::Red);
		break;
	}
}

void Button::Render(sf::RenderTarget& target)
{
	target.draw(*this);
	target.draw(m_text);
}

void Button::Reset(const sf::Vector2f& size_wh, const sf::Vector2f& pos, const uint32_t chSize)
{
	setSize(size_wh);
	SetPosition(pos);

	m_text.setCharacterSize(chSize);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f);
	m_text.setPosition(getPosition().x + getGlobalBounds().width / 2.f, getPosition().y + getGlobalBounds().height / 2.f);
}