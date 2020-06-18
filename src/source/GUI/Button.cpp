#include "stdHeader.hpp"

#include "Button.hpp"

using namespace GUI;

//Static members
float Button::m_press_time { 0.f };

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
	sf::Text& text,
	const sf::Color& color_idle,
	const sf::Color& color_hover,
	const sf::Color& color_active,
	const size_t index)
	: sf::RectangleShape{ size_wh },
	m_text{ text },
	m_color_idle{ color_idle },
	m_color_hover{ color_hover },
	m_color_active{ color_active },
	m_state{ States::IDLE },
	m_index{ index }
{
	sf::Transformable::setPosition(pos);
	setFillColor(m_color_idle);

	//Text by center
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f);

	m_text.setPosition(getPosition().x + getGlobalBounds().width / 2.f, getPosition().y + getGlobalBounds().height / 2.f);
}

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
			   sf::Font& font, const std::string& text, uint32_t ch_size,
			   const sf::Color& color_idle, 
			   const sf::Color& color_hover,
			   const sf::Color& color_active,
			   const size_t index)
	: sf::RectangleShape { size_wh },
	  m_text         { text,  font, ch_size },
	  m_color_idle   { color_idle   }, 
	  m_color_hover  { color_hover  }, 
	  m_color_active { color_active },
	  m_state        { States::IDLE },
	  m_index        { index }
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

////////////////////////////////////////////////////////////
// Accessors
////////////////////////////////////////////////////////////
const Button::States Button::getState() const
{
	return m_state;
}

const size_t Button::getIndex() const
{
	return m_index;
}

const sf::Text Button::getText() const
{
	return m_text;
}

const bool Button::isPressed() const
{
	if (m_state == States::ACTIVE)
		return true;

	return false;
}

////////////////////////////////////////////////////////////
// Modificators
////////////////////////////////////////////////////////////
void Button::setIndex(const size_t index)
{
	m_index = index;
}

void Button::setPosition(const sf::Vector2f& pos)
{
	sf::Transformable::setPosition(pos);

	//Text by center
	m_text.setPosition(pos.x + getGlobalBounds().width / 2.f, pos.y + getGlobalBounds().height / 2.f);
}

void Button::setText(const sf::Text& text)
{
	m_text = text;

	//Text by center
	m_text.setOrigin(m_text.getGlobalBounds().width / 2.f, m_text.getGlobalBounds().height / 2.f);

	m_text.setPosition(getPosition().x + getGlobalBounds().width / 2.f, getPosition().y + getGlobalBounds().height / 2.f);
}

void Button::setTextString(const std::string& str)
{
	m_text.setString(str);
}

////////////////////////////////////////////////////////////
// Info
////////////////////////////////////////////////////////////
std::string Button::getStringInfo() const
{
	std::stringstream result;

	result << "b_position x = " << getPosition().x << " " << "y = " << getPosition().y << '\n';
	result << "b_size x = "     << getSize().x << " " << "y = " << getSize().y << '\n';

	return result.str();
}


////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void Button::updateTimer(const float& dt)
{
	m_press_time += dt;
}

const bool Button::isTime()
{
	if (m_press_time >= m_max_press_time)
	{
		m_press_time = 0.f;
		return true;
	}

	return false;
}

void Button::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	/*Update the booleans for hover and pressed*/

	updateTimer(dt);
	m_state = States::IDLE;

	if (getGlobalBounds().contains(mouse_pos))
	{
		m_state = States::HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isTime())
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

void Button::render(sf::RenderTarget& target)
{
	target.draw(*this);
	target.draw(m_text);
}

void Button::reset(const sf::Vector2f& size_wh, const sf::Vector2f& pos, const uint32_t ch_size)
{
	setSize(size_wh);
	setPosition(pos);
	m_text.setCharacterSize(ch_size);
	m_text.setPosition(getPosition().x + getGlobalBounds().width / 2.f, getPosition().y + getGlobalBounds().height / 2.f);
}