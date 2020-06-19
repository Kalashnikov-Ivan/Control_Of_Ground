#include "stdHeader.hpp"

#include "TextureSelector.h"

using namespace GUI;

//Constructors
TextureSelector::TextureSelector(const sf::Vector2f& size, const sf::Vector2f& pos, const sf::Texture* texture_sheet, sf::Vector2f& grid_size)
	: sf::RectangleShape { size },
	m_sheet    { *texture_sheet },
	m_grid_size{ grid_size }, m_selector { grid_size }, m_selected_rect { 0, 0, static_cast<int>(m_grid_size.x), static_cast<int>(m_grid_size.y) },
	m_active   { false }, m_hidden { false }
{
	setPosition(pos);
	setFillColor(sf::Color(50, 50, 50, 100));
	setOutlineThickness(1.f);
	setOutlineColor(sf::Color::Red);

	m_sheet.setPosition(pos);
	
	if (m_sheet.getGlobalBounds().width >getGlobalBounds().width)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(getGlobalBounds().width), int(m_sheet.getGlobalBounds().height)));
	}

	if (m_sheet.getGlobalBounds().height > getGlobalBounds().height)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(m_sheet.getGlobalBounds().height), int(getGlobalBounds().width)));
	}

	m_selector.setPosition(pos);
	m_selector.setOutlineThickness(0.6f);
	m_selector.setOutlineColor(sf::Color::Green);
	m_selector.setFillColor(sf::Color::Transparent);
}

TextureSelector::~TextureSelector()
{

}

//Info
std::string TextureSelector::getStringInfo()
{
	std::stringstream result;

	result << "Selector::grid pos: " << m_mouse_pos_grid.x << ' ' << m_mouse_pos_grid.y << '\n';

	return result.str();
}

bool TextureSelector::isActive() const
{
	return m_active;
}

bool TextureSelector::isHidden() const
{
	return m_hidden;
}

//Accessors
sf::Vector2f TextureSelector::getGridSize() const
{
	return m_grid_size;
}

const sf::IntRect& TextureSelector::getSelectedRect() const
{
	return m_selected_rect;
}

//Functions
void inline TextureSelector::updateSelectorRect()
{
	m_selected_rect.left = static_cast<int>(m_selector.getPosition().x - getPosition().x);
	m_selected_rect.top = static_cast<int>(m_selector.getPosition().y - getPosition().y);
}

//Modificators
void TextureSelector::setPosition(const float x, const float y)
{
	sf::RectangleShape::setPosition(x, y);

	m_sheet.setPosition(x, y);
}

void TextureSelector::setPosition(const sf::Vector2f& pos)
{
	sf::RectangleShape::setPosition(pos);

	m_sheet.setPosition(pos);
}

void TextureSelector::setHidden(const bool option)
{
	m_hidden = option;
}

void TextureSelector::update(const sf::Vector2f& mouse_pos, const float& dt)
{
	if (!m_hidden)
	{
		if (getGlobalBounds().contains(mouse_pos))
			m_active = true;
		else
			m_active = false;

		if (m_active)
		{
			m_mouse_pos_grid.x = static_cast<unsigned>((mouse_pos.x - getPosition().x) / (m_grid_size.x));
			m_mouse_pos_grid.y = static_cast<unsigned>((mouse_pos.y - getPosition().y) / (m_grid_size.y));

			m_selector.setPosition(
				getPosition().x + m_mouse_pos_grid.x * m_grid_size.x,
				getPosition().y + m_mouse_pos_grid.y * m_grid_size.y
			);

			updateSelectorRect();
		}
	}
}

//Render
void TextureSelector::render(sf::RenderTarget& target)
{
	if (!m_hidden)
	{
		target.draw(*this);
		target.draw(m_sheet);

		if (m_active)
			target.draw(m_selector);
	}
}

void TextureSelector::reset(const sf::Vector2f& size, const sf::Vector2f& pos)
{
	setSize(size);
	setPosition(pos);
	
	m_sheet.setPosition(pos);

	if (m_sheet.getGlobalBounds().width > getGlobalBounds().width)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(getGlobalBounds().width), int(m_sheet.getGlobalBounds().height)));
	}

	if (m_sheet.getGlobalBounds().height > getGlobalBounds().height)
	{
		m_sheet.setTextureRect(sf::IntRect(0, 0, int(m_sheet.getGlobalBounds().height), int(getGlobalBounds().width)));
	}
}