#include "stdHeader.hpp"

#include "Button.hpp"

using namespace Core;

////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////
Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size_wh,
	sf::Font& font, const std::string& text, uint32_t ch_size,
	const sf::Color& color_idle, 
	const sf::Color& color_hover,
	const sf::Color& color_active)
	: m_shape{size_wh},
	  m_font{font}, m_text{ text,  font, ch_size },
	  m_color_idle {color_idle}, 
	  m_color_hover {color_hover}, 
	  m_color_active {color_active}
{
	m_shape.setPosition(pos);
	m_shape.setFillColor(m_color_idle);
	m_state = IDLE;

	m_text.setPosition(
		m_shape.getPosition().x + (m_shape.getGlobalBounds().width / 2.f) - m_text.getGlobalBounds().width / 2.f,
		(m_shape.getPosition().y + (m_shape.getGlobalBounds().height / 2.f) - m_text.getGlobalBounds().height / 2.f)
	);
}
Button::~Button()
{

}

////////////////////////////////////////////////////////////
// Functions
////////////////////////////////////////////////////////////
void Button::update(const sf::Vector2f& mouse_pos)
{
	/*Update the booleans for hover and pressed*/

	m_state = IDLE;

	if (m_shape.getGlobalBounds().contains(mouse_pos))
	{
		m_state = HOVER;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			m_state = ACTIVE;
	}

	switch (m_state)
	{
	case IDLE:
		m_shape.setFillColor(m_color_idle);
		break;
	case HOVER:
		m_shape.setFillColor(m_color_hover);
		break;
	case ACTIVE:
		m_shape.setFillColor(m_color_active);
		break;
	default:
		m_shape.setFillColor(sf::Color::Red);
		break;
	}
}

void Button::render(sf::RenderTarget* target)
{
	target->draw(m_shape);
	target->draw(m_text);
}

//Accessors
const bool Button::isPressed() const
{
	if (m_state == ACTIVE)
		return true;

	return false;
}